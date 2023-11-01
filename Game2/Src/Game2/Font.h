#pragma once

#include <iostream>
#include <map>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


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

	public:

		struct Character {
			unsigned int TextureID; // ID handle of the glyph texture
			glm::ivec2   Size;      // Size of glyph
			glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
			unsigned int Advance;   // Horizontal offset to advance to next glyph
		};

		void Initialize();
		//void MakeDisplayList(const std::string font);
		void MakeDisplayList(FT_Library ft, FT_Face face);
		void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color);
		void CleanupFreeType();


		std::map<GLchar, Character> Characters;
		std::string font_name;
		
	};
}
#endif // FONT_H