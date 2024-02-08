#include "pch.h"
#include "TempStateMachine.h"
#include "Application.h"

namespace Engine
{
	void Engine::StateMachine::UpdateEntities(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities)
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
					Walking(entity);
					break;
				case c_state::Attack:
					Attack(entity);
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
		TextureComponent* texture = dynamic_cast<TextureComponent*>(entity->GetComponent(ComponentType::Texture));
		// texture->SetAnimation(static_cast<int>(c_state::Static));
	}

	void StateMachine::Walking(Entity* entity)
	{
		TextureComponent* texture = dynamic_cast<TextureComponent*>(entity->GetComponent(ComponentType::Texture));
		texture->SetAnimation(static_cast<int>(c_state::Walking));
	}

	void StateMachine::Attack(Entity* entity)
	{
		TextureComponent* texture = dynamic_cast<TextureComponent*>(entity->GetComponent(ComponentType::Texture));
		CollisionComponent* collision = dynamic_cast<CollisionComponent*>(entity->GetComponent(ComponentType::Collision));
		texture->SetAnimation(static_cast<int>(c_state::Attack));
		Entity* target = collision->target;
		Stats::AttackTarget(5, entity, target);

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

