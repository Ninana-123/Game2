/******************************************************************************/
/*!
\file		FontManager.h
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
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/gtc/matrix_transform.hpp"

namespace Engine
{
	
	class FontManager
	{
	private:
		/*!
		\brief
		Private constructor for the FontManager class.
		*/
		FontManager();

		/*!
		\brief
		Deleted destructor to ensure FontManager is not deleted directly.
		*/
		~FontManager() = delete;

		/*!
		\brief
		OpenGL Vertex Array Object (VAO) used for font rendering.
		*/
		unsigned int VAO;

		/*!
		\brief
		OpenGL Vertex Buffer Object (VBO) used for font rendering.
		*/
		unsigned int VBO;

		/*!
		\brief
		Vector storing paths to different font types.
		*/
		std::vector <std::string> fontType;

		/*!
		\brief
		Static instance of FontManager for singleton pattern.
		*/
		static FontManager* mFontManager;

	public:
		/*!
		\brief
		Get the instance of the FontManager (singleton pattern).

		\return
		Pointer to the FontManager instance.
		*/
		static FontManager* GetInstance()
		{
			if (mFontManager == nullptr) // Check if the instance is not created yet
			{
				mFontManager = new FontManager();
			}
			return mFontManager;
		}

		/*!
		\brief
		Get the OpenGL Vertex Buffer Object (VBO) used for font rendering.

		\return
		OpenGL VBO identifier.
		*/
		unsigned int GetVBO();

		/*!
		\brief
		Get the OpenGL Vertex Array Object (VAO) used for font rendering.

		\return
		OpenGL VAO identifier.
		*/
		unsigned int GetVAO();

		/*!
		\brief
		Set the font to be used for rendering.

		\param fontPath
		Path to the font file.
		*/
		void setFont(std::string fontPath);
	};
	/* FontManager* FontManager::mFontManager = nullptr;*/
}