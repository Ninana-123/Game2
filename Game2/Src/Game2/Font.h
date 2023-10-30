#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H
#include <GL/glew.h>


    class Font
    {
    public:
        struct font_data
        {
            float fontSize;             // Holds The Height Of The Font.
            GLuint* characterTextures;    // Holds The Texture Id's
            GLuint displayListBase;    // Holds The First Display List Id

        
            void init(const char* fname, unsigned int h);

            // Free All The Resources Associated With The Font.
            void clean();
        };

      
        void print(const font_data& fontData, float positionX, float positionY, const char* text);
    };
