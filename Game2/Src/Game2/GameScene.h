/******************************************************************************/
/*!
\file		GameScene.h
\author		Kwok Jun Lin Wayne, k.junlinwayne, 2200751
\par		k.junlinwayne@digipen.edu
\date		25/01/2024
\brief		Contains the declarations of the Game Scene.

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#ifndef ENGINE_GAME_SCENE_H
#define ENGINE_GAME_SCENE_H

#include "Scene.h"
#include "Loader.h"
#include "EntityManager.h"

namespace Engine {
	extern const std::string GameSceneFilePath;
	
class GameScene : public Scene {
	public:
		/*!
		\brief Constructor for GameScene class.
		\param EM Pointer to the EntityManager instance.
		\param prefabManager Pointer to the PrefabManager instance.
		\param AM Pointer to the AssetManager instance.
		*/
		GameScene(std::shared_ptr<EntityManager> EM, PrefabManager* prefabManager, std::shared_ptr<AssetManager> AM) : gameLoader(EM, prefabManager, AM) {}
		
		/*!
		\brief Called when the game scene is loaded.
		*/
		void OnLoad() override;

		/*!
		\brief Called when the game scene is shut down.
		*/
		void OnShutDown() override;

	private:
		Loader gameLoader;
		EntityManager g_entityManager;
	};
}
#endif	ENGINE_GAME_SCENE_H