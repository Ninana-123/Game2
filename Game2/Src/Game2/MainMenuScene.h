/******************************************************************************/
/*!
\file		MainMenu.h
\author		Kwok Jun Lin Wayne, k.junlinwayne, 2200751
\par		k.junlinwayne@digipen.edu
\date		25/01/2024
\brief		Contains the declarations of the Scene for Main Menu.

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#ifndef ENGINE_MAINMENU_SCENE_H
#define ENGINE_MAINMENU_SCENE_H

#include "Scene.h"
#include "Loader.h"
#include "EntityManager.h"

namespace Engine {
	class MainMenuScene : public Scene {
	public:
		/*!
		\brief .
		\return .
		*/
		MainMenuScene(std::shared_ptr<Engine::EntityManager> EM, PrefabManager* prefabManager, std::shared_ptr<Engine::AssetManager> AM) : menuLoader(EM, prefabManager, AM) {}

		/*!
		\brief .
		\return .
		*/
		void OnLoad() override;

		/*!
		\brief .
		\return .
		*/
		void OnShutDown() override;

	private:
	Loader menuLoader;
	EntityManager m_entityManager;
	};
}
#endif	ENGINE_MAINMENU_SCENE_H