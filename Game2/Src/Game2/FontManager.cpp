/******************************************************************************/
/*!
\file		FontManager.cpp
\author 	Teo Sheen Yeoh
\par    	email: t.sheenyeoh@digipen.edu
\co         Tay Jun Feng Vance
            email: junfengvance.t@digipen.edu
\date   	August 29, 2023
\brief		This file provides the implementation for font rendering in the game engine.
            It contains functions to initialize the font rendering system, load font glyphs, and render text using OpenGL

            Copyright (C) 2023 DigiPen Institute of Technology.
            Reproduction or disclosure of this file or its contents without the prior
            written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
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