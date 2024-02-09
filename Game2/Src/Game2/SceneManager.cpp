/******************************************************************************/
/*!
\file		SceneManager.cpp
\author		Kwok Jun Lin Wayne, k.junlinwayne, 2200751
\par		k.junlinwayne@digipen.edu
\date		25/01/2024
\brief		Contains the implementations of the Scene Manager.

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#include "pch.h"
#include "SceneManager.h"

namespace Engine {

	void SceneManager::TransitionToScene(std::shared_ptr<Engine::Scene> scene){
		if (currentScene) {
			currentScene->OnShutDown();
		}
		currentScene = scene;
		currentScene->OnLoad();
	}
}