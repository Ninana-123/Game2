#include "pch.h"
#include "FontManager.h"

namespace Engine
{
    FontManager* FontManager::mFontManager = nullptr;
    FontManager::FontManager()
    {
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
        
    }

    

   unsigned int FontManager::GetVBO()
    {
       return VBO;
    }
      
   unsigned int FontManager::GetVAO()
   {
       return VAO;
   }

   void FontManager::setFont(std::string fontPath)
   {
      // fontType[i] = fontPath;
       fontType.push_back(fontPath);
   }

}