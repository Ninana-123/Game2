/******************************************************************************/
/*!
\file		TempStateMachine.cpp
\author 	Tristan Tham Rui Hong

\email		t.tham@digipen.edu

\date   	30/01/2024
\brief		This file contains the implementation of the states behaviours 
            that the entities will be using.
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "pch.h"
#include "TempStateMachine.h"
#include "Application.h"



namespace Engine
{	

	void Engine::StateMachine::UpdateEntities(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities, AudioEngine& audioEngine, AssetManager& assetManager)
	{
		// Iterate through entities that require pathfinding updates.
		for (const auto& it : *entities)
		{
			Entity* entity = it.second.get();

			if (entity->HasComponent(ComponentType::Logic))
			{
				BehaviourComponent* behaviourComponent = dynamic_cast<BehaviourComponent*>(entity->GetComponent(ComponentType::Logic));
				switch (behaviourComponent->GetState())
				{
				case c_state::Static:
					Idle(entity);
					break;
				case c_state::Idle:
					Idle(entity);
					break;
				case c_state::Walking:
					Walking(entity, audioEngine, assetManager);
					break;
				case c_state::Attack:
					Attack(entity, audioEngine, assetManager);
					break;
				case c_state::Death:
					Death(entity);
					break;
				default:
					break;
				}
			}
		}
	}

	void StateMachine::Idle(Entity* entity)
	{
		if (entity != nullptr) 
		{
			// TextureComponent* texture = dynamic_cast<TextureComponent*>(entity->GetComponent(ComponentType::Texture));
			// texture->SetAnimation(static_cast<int>(c_state::Static));
		}
		
	}

	void StateMachine::Walking(Entity* entity, AudioEngine& audioEngine, AssetManager& assetManager)
	{	
		static bool isFoot1Playing = true; // Start with footstep1
		static double lastFootSoundTime = glfwGetTime(); // Initialize the last foot sound time

		// Check if one second has elapsed since the last foot sound playback
		if (glfwGetTime() - lastFootSoundTime >= 1.0)
		{
			// If footstep1 is playing, stop it and play footstep2
			if (isFoot1Playing)
			{
				audioEngine.stopSound(*(assetManager.getAudio(AudioKey("sound_Foot1"))));
				audioEngine.playSound(*(assetManager.getAudio(AudioKey("sound_Foot2"))));
				isFoot1Playing = false;
			}
			// If footstep2 is playing, stop it and play footstep1
			else
			{
				audioEngine.stopSound(*(assetManager.getAudio(AudioKey("sound_Foot2"))));
				audioEngine.playSound(*(assetManager.getAudio(AudioKey("sound_Foot1"))));
				isFoot1Playing = true;
			}

			lastFootSoundTime = glfwGetTime(); // Update the last foot sound time
		}
		TextureComponent* texture = dynamic_cast<TextureComponent*>(entity->GetComponent(ComponentType::Texture));
		texture->SetAnimation(static_cast<int>(c_state::Walking));
		//audioEngine.stopSound(*(assetManager.getAudio(AudioKey("sound_Slash"))));
	}

	void StateMachine::Attack(Entity* entity, AudioEngine& audioEngine, AssetManager& assetManager)
	{
		//TextureComponent* texture = dynamic_cast<TextureComponent*>(entity->GetComponent(ComponentType::Texture));
		//CollisionComponent* collision = dynamic_cast<CollisionComponent*>(entity->GetComponent(ComponentType::Collision));
		//texture->SetAnimation(static_cast<int>(c_state::Attack));
		//Entity* target = collision->target;
		//Stats::AttackTarget(5, entity, target);
		//audioEngine.playSound(*(assetManager.getAudio(AudioKey("sound_Slash"))));
		static bool isAudioAttackPlaying = false;
		static double lastSoundTime = glfwGetTime(); // Initialize the last sound time

		// Check if one second has elapsed since the last sound playback
		if (glfwGetTime() - lastSoundTime >= 1.0)
		{
			// If audio is not playing, start playing it
			if (!isAudioAttackPlaying)
			{
				// Play the sound
				audioEngine.playSound(*(assetManager.getAudio(AudioKey("sound_Slash"))));
				isAudioAttackPlaying = true;
				audioEngine.stopSound(*(assetManager.getAudio(AudioKey("sound_Foot1"))));
				audioEngine.stopSound(*(assetManager.getAudio(AudioKey("sound_Foot2"))));
			}
			else
			{
				// Stop the sound playback
				audioEngine.stopSound(*(assetManager.getAudio(AudioKey("sound_Slash"))));
				isAudioAttackPlaying = false;
			}

			lastSoundTime = glfwGetTime(); // Update the last sound time
		}
		TextureComponent* texture = dynamic_cast<TextureComponent*>(entity->GetComponent(ComponentType::Texture));
		CollisionComponent* collision = dynamic_cast<CollisionComponent*>(entity->GetComponent(ComponentType::Collision));
		texture->SetAnimation(static_cast<int>(c_state::Attack));
		Entity* target = collision->target;
		Stats::AttackTarget(5, entity, target);
		//audioEngine.stopSound(*(assetManager.getAudio(AudioKey("sound_Foot1"))));
		//audioEngine.stopSound(*(assetManager.getAudio(AudioKey("sound_Foot2"))));
		
	}

	void StateMachine::Death(Entity* entity)
	{
		TextureComponent* texture = dynamic_cast<TextureComponent*>(entity->GetComponent(ComponentType::Texture));
		CollisionComponent* collision = dynamic_cast<CollisionComponent*>(entity->GetComponent(ComponentType::Collision));
		texture->SetAnimation(static_cast<int>(c_state::Death));
		collision->disableCollision = true;
		//entity->components.erase(ComponentType::Collision);
	}

}

