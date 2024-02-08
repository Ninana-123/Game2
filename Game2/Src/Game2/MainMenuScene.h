#ifndef ENGINE_MAINMENU_SCENE_H
#define ENGINE_MAINMENU_SCENE_H

#include "Scene.h"
#include "Loader.h"

namespace Engine {
	class MainMenuScene : public Scene {
	public:
		MainMenuScene(std::shared_ptr<Engine::EntityManager> EM, PrefabManager* prefabManager, std::shared_ptr<Engine::AssetManager> AM) : menuLoader(EM, prefabManager, AM) {}

		void OnLoad() override;

		void OnShutDown() override;

	private:
	Loader menuLoader;
	};
}
#endif	ENGINE_MAINMENU_SCENE_H