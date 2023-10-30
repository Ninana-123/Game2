#include "pch.h"
#include "Font.h"

int nextPowerOf2(int value) 
{
    int result = 1;
    while (result < value) 
    {
        result <<= 1;
    }
    return result;
}

void makeDisplayList(FT_Face face, char character, GLuint listBase, GLuint* textureBase) 
{
    if (FT_Load_Char(face, character, FT_LOAD_RENDER)) 
    {
        throw std::runtime_error("FT_Load_Char failed");
    }

    FT_GlyphSlot glyphSlot = face->glyph;

    int textureWidth = nextPowerOf2(glyphSlot->bitmap.width);
    int textureHeight = nextPowerOf2(glyphSlot->bitmap.rows);

    GLubyte* expandedTextureData = new GLubyte[2 * textureWidth * textureHeight];

    for (int j = 0; j < textureHeight; j++)
    {
        for (int i = 0; i < textureWidth; i++)
        {
            int index = 2 * (i + j * textureWidth);

            if (i < glyphSlot->bitmap.width && j < glyphSlot->bitmap.rows)
            {
                expandedTextureData[index] = glyphSlot->bitmap.buffer[i + glyphSlot->bitmap.width * j];
                expandedTextureData[index + 1] = expandedTextureData[index];
            }
            else 
            {
                expandedTextureData[index] = 0;
                expandedTextureData[index + 1] = 0;
            }
        }
    }

    glBindTexture(GL_TEXTURE_2D, textureBase[character]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expandedTextureData);

    delete[] expandedTextureData;

    glNewList(listBase + character, GL_COMPILE);
    glBindTexture(GL_TEXTURE_2D, textureBase[character]);

    // Rendering in 2D space
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(0, static_cast<GLfloat>(glyphSlot->bitmap.rows));
    glTexCoord2f(0, 1); glVertex2f(0, 0);
    glTexCoord2f(1, 1); glVertex2f(static_cast<GLfloat>(glyphSlot->bitmap.width), 0);
    glTexCoord2f(1, 0); glVertex2f(static_cast<GLfloat>(glyphSlot->bitmap.width), static_cast<GLfloat>(glyphSlot->bitmap.rows));
    glEnd();

    glEndList();
}

void Font::font_data::init(const char* fontFileName, unsigned int fontSize) 
{
    // Allocate memory for storing texture IDs for characters
    characterTextures = new GLuint[128];

    // Set the font size
    this->fontSize = fontSize;

    // Initialize the FreeType library
    FT_Library library;
    if (FT_Init_FreeType(&library)) 
    {
        throw std::runtime_error("Failed to initialize FreeType library");
    }

    // Load the font face from the specified font file
    FT_Face fontFace;
    if (FT_New_Face(library, fontFileName, 0, &fontFace)) 
    {
        throw std::runtime_error("Failed to load the font face, possibly due to an issue with the font file");
    }

    // Set the pixel size of the font
    FT_Set_Pixel_Sizes(fontFace, fontSize, fontSize);

    // Generate display lists for rendering characters
    displayListBase = glGenLists(128);

    // Generate OpenGL textures for characters
    glGenTextures(128, characterTextures);

    // Create display lists and textures for the first 128 ASCII characters
    for (unsigned char character = 0; character < 128; character++) 
    {
        makeDisplayList(fontFace, character, displayListBase, characterTextures);
    }

    // Release resources associated with the font face
    FT_Done_Face(fontFace);

    // Release FreeType library resources
    FT_Done_FreeType(library);
}


void Font::print(const font_data& fontData, float positionX, float positionY, const char* text) 
{
    // Set up projection matrix for screen coordinates
    glPushAttrib(GL_TRANSFORM_BIT);
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(viewport[0], viewport[2], viewport[1], viewport[3], -1, 1);
    glPopAttrib();

    GLuint displayListBase = fontData.displayListBase;
    float fontSize = fontData.fontSize / 0.63f;

    // Split the text into lines
    std::vector<std::string> lines;
    const char* lineStart = text;
    const char* currentCharacter;
    for (currentCharacter = text; *currentCharacter; currentCharacter++) 
    {
        if (*currentCharacter == '\n') 
        {
            lines.emplace_back(lineStart, currentCharacter - lineStart);
            lineStart = currentCharacter + 1;
        }
    }
    lines.emplace_back(lineStart, currentCharacter - lineStart);

    // Set up OpenGL states for text rendering
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);

    // Get the modelview matrix
    float modelViewMatrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, modelViewMatrix);

    // Render each line of text
    for (size_t i = 0; i < lines.size(); i++)
    {
        glPushMatrix();
        glLoadIdentity();
        glTranslatef(positionX, positionY - fontSize * i, 0);
        glMultMatrixf(modelViewMatrix);

        // Call display lists for rendering
        glCallLists(static_cast<GLsizei>(lines[i].length()), GL_UNSIGNED_BYTE, lines[i].c_str());

        glPopMatrix();
    }

    // Restore the previous projection matrix
    glPushAttrib(GL_TRANSFORM_BIT);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}



void Font::font_data::clean()
{
    glDeleteLists(displayListBase, 128);
    glDeleteTextures(128, characterTextures);
    delete[] characterTextures;
}
