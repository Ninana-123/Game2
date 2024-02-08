#include "pch.h"
#include "SceneManager.h"

namespace Engine {

	void SceneManager::TransitionToScene(Scene* nextScene){
		if (currentScene) {
			currentScene->OnShutDown();
			delete currentScene;
		}
		currentScene = nextScene;
		currentScene->OnLoad();
	}
}