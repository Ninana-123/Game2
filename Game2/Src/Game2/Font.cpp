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
        Shader shader("Resource/Shaders/Shader.vert", "Resource/Shaders/Shader.frag", "Resource/Shaders/Shader2.vert", "Resource/Shaders/Shader2.frag", "Resource/Shaders/Shader3.vert", "Resource/Shaders/Shader3.frag");
        shader.SetActiveShaderSet(3);
        shader.Initialize();
        shader.Bind();



        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(fscreenWidth), 0.0f, static_cast<float>(fscreenHeight));
        glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));


        //int displayWidth, displayHeight;
        //glfwGetFramebufferSize(glfwGetCurrentContext(), &displayWidth, &displayHeight);
        //glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(displayWidth), 0.0f, static_cast<float>(displayHeight));
        //glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));


        // FreeType
        if (FT_Init_FreeType(&ft))
        {
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
            exit(-1);
        }

        // find path to font
        //pathName = "Resource/Fonts/arial.ttf";
        pathName = "Resource/Fonts/Inkfree.ttf";
        if (!std::filesystem::exists(pathName)) {
            std::cout << "ERROR::FREETYPE: Font file does not exist at path: " << pathName << std::endl;
            exit(-1);
        }
        else 
        {
        std::cout << "Font file path: " << pathName << std::endl;
        }

    
        // Load first 128 characters of ASCII set
        if (FT_New_Face(ft, pathName.c_str(), 0, &face)) {
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
            exit(-1);
        }

        // Set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, 48);

        // Disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // configure VAO/VBO for texture quads
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Now you can call MakeDisplayList to load glyphs
        MakeDisplayList(pathName);



        shader.Unbind();
    }

    void font::MakeDisplayList(const std::string pathname) 
    {   
       
       
        // Load first 128 characters of ASCII set
        for (unsigned char c = 0; c <= 128; c++) 
        {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) 
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph for character '" << c << "'" << std::endl;
                continue;
            }

            // generate texture
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

    }


    void font::RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color)
    {
        // activate corresponding render state	
        shader.SetActiveShaderSet(3);
        shader.Bind();
        glUniform3f(glGetUniformLocation(shader.GetID(), "textColor"), color.x, color.y, color.z);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        float halfWidth;
        float lengthWidth{};
        for (char c : text)
        {
            Character ch = Characters[c];
            lengthWidth += (ch.Advance >> 6) * scale ;
            
        }

        halfWidth = lengthWidth / 2.0f;
        float newx =  x- halfWidth;

        // iterate through all characters
        for (char c : text)
        {
            
            Character ch = Characters[c];

            float xpos = newx + ch.Bearing.x * scale ;
            float ypos = y - (ch.Size.y - ch.Bearing.y) * scale ;

            float width = ch.Size.x * scale ;
            float height = (ch.Size.y) * scale ;

            // Debugging lines
            std::cout << "Character: " << c << std::endl;
            std::cout << "Position: x=" << xpos << ", y=" << ypos << std::endl;
            std::cout << "Width: " << width << ", Height: " << height << std::endl;
            std::cout << "Color: R=" << color.x << ", G=" << color.y << ", B=" << color.z << std::endl;

            // update VBO for each character
            float vertices[6][4] = {
                { xpos,         ypos + height,   0.0f, 0.0f },
                { xpos,         ypos,            0.0f, 1.0f },
                { xpos + width, ypos,            1.0f, 1.0f },

                { xpos,         ypos + height,   0.0f, 0.0f },
                { xpos + width, ypos,            1.0f, 1.0f },
                { xpos + width, ypos + height,   1.0f, 0.0f }
            };

            // render glyph texture over quad
            std::cout << "Binding Texture for Character: " << c << std::endl;
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);

            std::cout << "Updating VBO for Character: " << c << std::endl;
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            if (glIsBuffer(VBO))
            {
                std::cout << "ok\n";
            }
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            std::cout << "Drawing Character: " << c << std::endl;
            glDrawArrays(GL_TRIANGLES, 0, 6);

            // now advance cursors for next glyph (note that advance is the number of 1/64 pixels)
            newx += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide the amount of 1/64th pixels by 64 to get the amount of pixels))
           

            std::cout << "Advance: " << newx << std::endl;
            std::cout << "------------------------" << std::endl;

        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        shader.Unbind();
    }



    void font::CleanupFreeType() 
    {
        FT_Done_Face(face);
        FT_Done_FreeType(ft);

    }
}
