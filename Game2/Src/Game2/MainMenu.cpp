/******************************************************************************/
/*!
\file		MainMenu.cpp
\author 	Kwok Jun Lin Wayne
\par    	email: k.junlinwayne@digipen.edu
\date   	08/01/2024
\brief		This file contains the

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "pch.h"
#include "MainMenu.h"
#include "Application.h"
#include "Loader.h"
std::string nextSceneFilePath = "Resource/Scenes/Level0Test.txt";

namespace Engine {

	MainMenu::MainMenu() : menuSceneFilePath("Resource/Scenes/MainMenu.txt"), loader(loader) {

	}

	MainMenu::~MainMenu() {

	}

	void MainMenu::Initialize() {
		LoadMainMenuScene();
	}

	void MainMenu::Render() {

	}

	void MainMenu::HandleInput() {

	}

	void MainMenu::TransitionToGame() {
		//set the next scene file path
		
		loader.LoadScene(nextSceneFilePath);
	}

	void MainMenu::LoadMainMenuScene()
	{
		loader.LoadScene(menuSceneFilePath);
	}
}