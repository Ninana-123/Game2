/******************************************************************************/
/*!
\file		Tower.cpp
\author 	Tristan Tham Rui Hong
\par    	email: t.tham@digipen.edu
\date   	01/03/2924
\brief		Declaration of the ScriptSystem class

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "pch.h"
#include "Tower.h"
#include "Application.h"
#include "Arrow.h"
#include "CollisionSystem.h"

namespace Engine
{
	Tower::Tower (Entity* entity_) : entity(entity_)
	{
		EM = g_ScriptFactory->GetScriptSystem()->QueryEM();
		PM = EM->QueryPM();

		// Initialize the entity's transform component
		entityTransform = dynamic_cast<TransformComponent*>(entity->GetComponent(ComponentType::Transform));
		
	}

	void Tower::Update()
	{
		entityScript = dynamic_cast<ScriptComponent*>(entity->GetComponent(ComponentType::Script));
		
		//Update Existing Arrows first
		for (auto it = arrows.begin(); it != arrows.end();)
		{
			Arrow* arrow = *it;
			arrow->Update();

			if (arrow->Hit())
			{
				// Arrow has hit its target, remove it from the list and delete it
				it = arrows.erase(it);
				delete arrow;
				std::cout << "Deleted Arrow" << std::endl;
			}
			else
			{
				++it;
			}
		}

		if (alive)
		{
			
			//Retrieve target
			if (Target())
			{

				//Shoot Arrow
				if (counter <= 0.f)
				{
					Shoot(target);

					counter = 1.f / firerate;
				}

				counter -= static_cast<float>(fixedDeltaTime);
			}
			else
			{
				return;
			}
		}

		if (hp <= 0.f)
		{
			alive = false;
			IsDead();
		}
	}

	void Tower::Shoot(Entity* target_)
	{	
		//Null check
		if (!entity)
		{
			std::cerr << "Target entity is null." << std::endl;
			return;
		}

		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(entity->GetComponent(ComponentType::Transform));
		if (!transformComponent)
		{
			std::cerr << "Parent has no TransformComponent." << std::endl;
			return;
		}

		VECTORMATH::Vec2 startingPosition = transformComponent->position;

		Arrow* arrow = new Arrow(target_, damage, startingPosition);
		arrows.push_back(arrow);
		count++;
		std::cout << "Fired Arrow " << count << std::endl;
	}

	bool Tower::Target()
	{
		// Initialize variables to track the closest target
		float closestDistance = std::numeric_limits<float>::max();
		Entity* closestTarget = nullptr;

		// Query entities with type ScriptType::archer
		targets = EM->QueryScriptEntitiesWithoutType(ScriptType::tower);

		// Check each target
		for (Entity* potentialTarget : targets)
		{
			// Get the transform component of the target
			TransformComponent* potentialTargetTransform = dynamic_cast<TransformComponent*>(potentialTarget->GetComponent(ComponentType::Transform));
			if (!potentialTargetTransform)
			{
				// Skip if the target doesn't have a transform component
				continue;
			}

			ScriptComponent* targetScript = dynamic_cast<ScriptComponent*>(potentialTarget->GetComponent(ComponentType::Script));
			if (targetScript && targetScript->alive && targetScript->run)
			{
				// Calculate the distance between the tower and the target
				VECTORMATH::Vec2 distanceVector = entityTransform->position - potentialTargetTransform->position;
				float distance = std::sqrt(distanceVector.x * distanceVector.x + distanceVector.y * distanceVector.y);

				// Check if the target is within range
				if (distance <= range)
				{
					// Check if this target is closer than the current closest target
					if (distance < closestDistance)
					{
						closestDistance = distance; // Update closest distance
						closestTarget = potentialTarget; // Update closest target
					}
				}
			}		
		}

		// Set the closest target as the tower's target
		target = closestTarget;

		// Return true if a target was found
		return (closestTarget != nullptr);
	}

	void Tower::IsDead()
	{
		entityScript = dynamic_cast<ScriptComponent*>(entity->GetComponent(ComponentType::Script));
		entityScript->alive = false;

		TextureComponent* textureComponent = dynamic_cast<TextureComponent*>(entity->GetComponent(ComponentType::Texture));
		textureComponent->textureKey = { 4 , 4 };
	}
}

