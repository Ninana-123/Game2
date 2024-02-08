#include "pch.h"
#include "GameScene.h"

const std::string GameSceneFilePath = "Resource/Scenes/Level0Test.txt";

namespace Engine {
	void GameScene::OnLoad()
	{
		gameLoader.LoadScene(GameSceneFilePath);
	}

	void GameScene::OnShutDown()
	{
	}
}