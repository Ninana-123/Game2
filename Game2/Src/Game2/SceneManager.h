#ifndef ENGINE_SCENE_MANAGER_H
#define ENGINE_SCENE_MANAGER_H
#include "Scene.h"

namespace Engine {
	class SceneManager {
	public:
		void TransitionToScene(Scene* nextScene);

	private:
		Scene* currentScene = nullptr;
	};

}
#endif	ENGINE_SCENE_MANAGER_H