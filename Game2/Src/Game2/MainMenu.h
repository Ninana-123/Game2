/******************************************************************************/
/*!
\file		MainMenu.h
\author 	Kwok Jun Lin Wayne
\par    	email: k.junlinwayne@digipen.edu
\date   	08/01/2024
\brief		This file contains the 

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "Loader.h"

#ifndef ENGINE_MAINMENU_H
#define ENGINE_MAINMENU_H

namespace Engine {

	class MainMenu {
	public:
		MainMenu();
		~MainMenu();

		void Initialize();
		void Render();
		void HandleInput();
		void TransitionToGame();
		void LoadMainMenuScene();

	private:
		std::string menuSceneFilePath;
		Loader loader;
	};
}
#endif // !ENGINE_MAINMENU_H