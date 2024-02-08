#include "pch.h"
#include "MainMenuScene.h"

const std::string MainMenuSceneFilePath = "Resource/Scenes/MainMenu.txt";

namespace Engine {

	void MainMenuScene::OnLoad()
	{	
		menuLoader.LoadScene(MainMenuSceneFilePath);
		
	}

	void MainMenuScene::OnShutDown()
	{
	}
}