#include "pch.h"
#include "Font.h"

namespace Engine
{

    void font::Initialize() {
      

        // OpenGL state
        // ------------
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // compile and setup the shader
        // ----------------------------
        const float fscreenWidth = 1280.0f;
        const float fscreenHeight = 720.0f;
        Shader shaderSet1("Resource/Shaders/Shader.vert", "Resource/Shaders/Shader.frag", "Resource/Shaders/Shader2.vert", "Resource/Shaders/Shader2.frag");
        glOrtho(0, fscreenWidth, 0, fscreenHeight, -1, 1);
        shaderSet1.Initialize();
        shaderSet1.Bind();
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(fscreenWidth), 0.0f, static_cast<float>(fscreenHeight), -1.0f, 1.0f);
        glUniformMatrix4fv(glGetUniformLocation(shaderSet1.GetID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
     

        // FreeType
        FT_Library ft;
        if (FT_Init_FreeType(&ft))
        {
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
            exit(-1);
        }

        // find path to font
        std::string relativePath = "Resource/Fonts/arial.ttf";
        std::filesystem::path fontPath = std::filesystem::canonical(relativePath);
        std::string font_name = fontPath.string();

        if (std::filesystem::exists(fontPath)) {
            font_name = fontPath.string();
            std::cout << "Font file path: " << font_name << std::endl;
        }
        else {
            std::cout << "ERROR::FREETYPE: Failed to load font file path" << std::endl;
            exit(-1);
        }

        // Load first 128 characters of ASCII set
        FT_Face face;
        if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
            exit(-1);
        }

        // Set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, 48);

        // Disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // Now you can call MakeDisplayList to load glyphs
        MakeDisplayList(ft, face);

       
    }

        void font::MakeDisplayList(FT_Library ft, FT_Face face) {     // Load first 128 characters of ASCII set
       
       
        // Load first 128 characters of ASCII set
            for (unsigned char c = 'A'; c <= 'Z'; c++) {
                if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                    std::cout << "ERROR::FREETYTPE: Failed to load Glyph for character '" << c << "'" << std::endl;
                    continue;
                }

            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        // destroy FreeType once we're finished
        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        // configure VAO/VBO for texture quads
        // -----------------------------------

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }


    // render line of text
    // -------------------
    void font::RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color)
    {
        // activate corresponding render state	
        shader.Bind();
        glUniform3f(glGetUniformLocation(shader.GetID(), "textColor"), color.x, color.y, color.z);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        // iterate through all characters
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++)
        {
            Character ch = Characters[*c];


            float xpos = x + (ch.Bearing.x >> 6) * scale;
            float ypos = y - (ch.Size.y >> 6 - ch.Bearing.y >> 6) * scale;
            std::cout << "Position: x=" << xpos << ", y=" << ypos << std::endl;

            float w = (ch.Size.x >> 6) * scale;
            float h = (ch.Size.y >> 6) * scale;
            std::cout << "Width: x=" << w << ",Height: y=" << h << std::endl;


           
            // update VBO for each character
            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
            };
            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))

            std::cout << "Position: x=" << xpos << ", y=" << ypos << std::endl;
            std::cout << "Character: " << *c << std::endl;
            std::cout << "Text: " << text << std::endl;

        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);


    }


    void font::CleanupFreeType() 
    {
        FT_Done_Face(face);
        FT_Done_FreeType(ft);

    }
}