#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/gtc/matrix_transform.hpp"

namespace Engine
{
	
	class FontManager 
	{
	private: 
		FontManager();
		~FontManager() = delete;
		unsigned int VAO;
		unsigned int VBO;
		std::vector <std::string> fontType;

		static FontManager* mFontManager;
	public:
		//static FontManager* GetInstance() { return mFontManager;  }
        static FontManager* GetInstance()
        {
            if (mFontManager == nullptr) // Check if the instance is not created yet
            {
                mFontManager = new FontManager(); 
            }
            return mFontManager;
        }
		unsigned int GetVBO();
		unsigned int GetVAO();
		void setFont(std::string fontPath);
	};
   /* FontManager* FontManager::mFontManager = nullptr;*/
}
