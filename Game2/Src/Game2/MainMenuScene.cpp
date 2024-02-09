/******************************************************************************/
/*!
\file		MainMenuScene.cpp
\author		Kwok Jun Lin Wayne, k.junlinwayne, 2200751
\par		k.junlinwayne@digipen.edu
\date		25/01/2024
\brief		Contains the implementations of the Main Menu Scene.

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#include "pch.h"
#include "MainMenuScene.h"

const std::string MainMenuSceneFilePath = "Resource/Scenes/MainMenu.txt";

namespace Engine {

	void MainMenuScene::OnLoad()
	{	
		menuLoader.LoadScene(MainMenuSceneFilePath);
		// Add entities to storage when they are created
		auto entities = m_entityManager.GetEntities();
		for (const auto& pair : *entities) {
			m_entityManager.AddToStorage(pair.first);
		}
	}

	void MainMenuScene::OnShutDown()
	{
		m_entityManager.DestroyEntitiesInStorage();
	}
}