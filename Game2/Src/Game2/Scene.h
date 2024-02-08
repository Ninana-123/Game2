#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H

namespace Engine {
	class Scene {
	public: 
		virtual ~Scene() {} //virtual destructor
		virtual void OnLoad() = 0;
		virtual void OnShutDown() = 0;

	};
}
#endif	ENGINE_SCENE_H