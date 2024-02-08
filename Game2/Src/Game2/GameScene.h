#ifndef ENGINE_GAME_SCENE_H
#define ENGINE_GAME_SCENE_H

#include "Scene.h"
#include "Loader.h"
namespace Engine {
	class GameScene : public Scene {
	public:
		GameScene(std::shared_ptr<EntityManager> EM, PrefabManager* prefabManager, std::shared_ptr<AssetManager> AM) : gameLoader(EM, prefabManager, AM) {}

		void OnLoad() override;

		void OnShutDown() override;

	private:
		Loader gameLoader;
	};
}
#endif	ENGINE_GAME_SCENE_H