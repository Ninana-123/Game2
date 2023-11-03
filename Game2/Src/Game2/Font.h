/******************************************************************************/
/*!
\file		font.cpp
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


#pragma once

#include <iostream>
#include <map>
#include <string>
#include "Vector2d.h"


#include <GL/glew.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Shader.h"

#ifndef FONT_H
#define FONT_H

namespace Engine {

	class font 
	{

	private:
		GLuint VAO{}, VBO{};
		FT_Face face{};
		FT_Library ft{};
		const float fscreenWidth = 1280.0f;
		const float fscreenHeight = 720.0f;

	public:

		struct Character {
			unsigned int TextureID; // ID handle of the glyph texture
			glm::ivec2   Size;      // Size of glyph
			glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
			unsigned int Advance;   // Horizontal offset to advance to next glyph
		};

		struct TextInfo
		{
			std::string text;
			glm::ivec2 pos;
			int scale;
			glm::ivec2 color;
		};

		void Initialize();
		//void MakeDisplayList(const std::string font);
		void MakeDisplayList(const std::string pathname);
		void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color);
		void CleanupFreeType();

		std::string pathName;
		std::map <char , Character> Characters;
		std::string font_name;
		// unsigned int texture;

		//GLFWwindow* window{};

		
	};
}
#endif // FONT_H