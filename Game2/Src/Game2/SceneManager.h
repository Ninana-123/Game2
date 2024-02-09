/******************************************************************************/
/*!
\file		SceneManager.h
\author		Kwok Jun Lin Wayne, k.junlinwayne, 2200751
\par		k.junlinwayne@digipen.edu
\date		25/01/2024
\brief		Contains the declarations of the Scene Manager.

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#ifndef ENGINE_SCENE_MANAGER_H
#define ENGINE_SCENE_MANAGER_H
#include "Scene.h"

namespace Engine {
	class SceneManager {
	public:
		/*!
		\brief Transitions to a new scene.
		\param scene Pointer to the scene to transition to.
		*/
		void TransitionToScene(std::shared_ptr<Engine::Scene> scene);

	private:
		std::shared_ptr<Engine::Scene> currentScene;
	};

}
#endif	ENGINE_SCENE_MANAGER_H