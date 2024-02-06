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
#include "AssetManager.h"

std::string nextSceneFilePath = "Resource/Scenes/Level0Test.txt";

namespace Engine {
std::shared_ptr<Loader> load = nullptr;
PrefabManager PreManager;
std::shared_ptr<EntityManager> EntManager;

	MainMenu::MainMenu() 
		: menuSceneFilePath("Resource/Scenes/MainMenu.txt") {

	}

	MainMenu::~MainMenu() {

	}

	void MainMenu::Initialize() {
		EntManager = std::make_shared<Engine::EntityManager>();
		assManager = std::make_shared<Engine::AssetManager>();

		load = std::make_unique<Engine::Loader>(EntManager, &PreManager, assManager);

		LoadMainMenuScene();
	}

	void MainMenu::Render() {

	}

	void MainMenu::HandleInput() {

	}

	void MainMenu::TransitionToGame() {
		//set the next scene file path
		
		load->LoadScene(nextSceneFilePath);
	}

	void MainMenu::LoadMainMenuScene()
	{
		load->LoadScene(menuSceneFilePath);
	}
}