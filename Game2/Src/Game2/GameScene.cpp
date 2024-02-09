/******************************************************************************/
/*!
\file		GameScene.cpp
\author		Kwok Jun Lin Wayne, k.junlinwayne, 2200751
\par		k.junlinwayne@digipen.edu
\date		25/01/2024
\brief		Contains the implementations of the Game Scene.

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#include "pch.h"
#include "GameScene.h"

namespace Engine {
	const std::string GameSceneFilePath = "Resource/Scenes/Level0Test.txt";

	void GameScene::OnLoad()
	{
		gameLoader.LoadScene(GameSceneFilePath);
	}

	void GameScene::OnShutDown()
	{
		for (auto& pair : g_entityManager)
		{
			g_entityManager.DestroyEntity(pair.first);
		}
	}
}