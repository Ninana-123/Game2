#pragma once

#include <iostream>
#include <string>
#include <memory>
#include "Entity.h"
#include "Component.h"
#include "AssetManager.h"

namespace Engine
{
	class StateMachine
	{
	public:
		
		assetManager->AddAudioPath(AudioKey("sound_Slash"), "Resource/Audio/samurai_slash.wav");
		assetManager->loadAudio(AudioKey("sound_Slash"));
		assetManager->getAudio(AudioKey("sound_Slash"))->setVolume(0.5f);
		AudioEngine audio;

		std::shared_ptr<Engine::AssetManager> assetManager;

		void UpdateEntities(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities);

		void Idle(Entity* entity);

		void Walking(Entity* entity);

		void Attack(Entity* entity);

		void Death(Entity* entity);
	};
	
}
