/******************************************************************************/
/*!
\file		Font.h
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
#ifndef ENGINE_FONT_H
#define ENGINE_FONT_H

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

namespace Engine {

	class font
	{

	private:
		GLuint VAO{}, VBO{};
		FT_Face face1{};
		FT_Face face2{};
		FT_Library ft{};
		const float fscreenWidth = 1280.0f;
		const float fscreenHeight = 720.0f;
		FT_Face currentFace{};

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

		/*!
		\brief
		Initialize the font rendering system.

		This function initializes OpenGL state, compiles shaders, and sets up FreeType library.
		*/
		void Initialize();

		/*!
		\brief
		Load the glyphs of the specified font and create display lists for rendering text.

		\param pathname
		Path to the font file.
		*/
		void MakeDisplayList(const std::string pathname);

		/*!
		\brief
		Render the specified text at the given position, scale, and color using the provided shader.

		\param shader
		Shader program to use for rendering.

		\param text
		Text to render.

		\param x
		X-coordinate of the starting position.

		\param y
		Y-coordinate of the starting position.

		\param scale
		Scale factor for the text.

		\param color
		Color of the text.
		*/
		void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color);

		/*!
		\brief
		Clean up the FreeType library resources.

		This function should be called to release resources acquired by FreeType library.
		*/
		void CleanupFreeType();

		/*!
		\brief
		Switch to a different font by specifying the font index.

		\param fontIndex
		Index of the font to switch to.
		*/
		void SwitchFont(int fontIndex);

		/*!
		\brief
		Load glyphs for the specified FreeType face.

		\param face
		FreeType face for which to load glyphs.
		*/
		void LoadGlyphsForFace(FT_Face face);

		std::string pathName, pathName2;
		std::map <char, Character> Characters1;
		std::map <char, Character> Characters2;
		std::string font_name;
		unsigned int texture = 0;

		//GLFWwindow* window{};
	};
}
#endif  ENGINE_FONT_H