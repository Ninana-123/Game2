
#include "pch.h"
#include "GraphicsSystem.h"
#include "pch.h"
#include "Arrow.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Window.h"


namespace Engine {
	EntityManager entitymanager;
	

	float ARROW_HALF_X = 0;
	float ARROW_HALF_Y = 0;

#define ARROW_BOUNDARY_X (ARROW_HALF_X + 100)
#define ARROW_BOUNDARY_Y (ARROW_HALF_Y + 100)

#define ARROW_SPEED 200.f



	void Remove_Arrow(int index, ArrowPool& pool) {
		pool.activeArrow[index]->enabled = false;
		if (index < (pool.activeSize - 1)) {
			Arrow* temp = pool.activeArrow[index];
			pool.activeArrow[index] = pool.activeArrow[pool.activeSize - 1];
			pool.activeArrow[pool.activeSize - 1] = temp;
		}
		pool.activeSize -= 1;
	}

	void Add_Arrow(ArrowPool& pool, VECTORMATH::Vector2D archPos, VECTORMATH::Vector2D playerPos) {
		for (int i = 0; i < ARROW_COUNT; i++) {
			if (pool.activeArrow[i]->enabled == false) {
				pool.activeArrow[i]->enabled = true;
				pool.activeArrow[i]->transform.position = archPos;
				pool.activeArrow[i]->transform.scaleX = 2;
				pool.activeArrow[i]->transform.scaleY = 2;
				pool.activeArrow[i]->transform.rot = std::atan2(playerPos.y - archPos.y, playerPos.x - archPos.x);
				VECTORMATH::Vector2D direction1;
				VECTORMATH::Vector2D temp = playerPos - archPos;
				Vector2DNormalize(direction1, temp);
				pool.activeArrow[i]->direction = direction1;
				pool.activeSize += 1;
				break;
			}
		}
	}

	void Init_ArrowPool(ArrowPool& pool) {
	
		EntityID arrowentityID = entitymanager.CreateEntity();
		entitymanager.GetEntity(arrowentityID)->AddNewComponent(ComponentType::Transform);
		auto transformComponent = dynamic_cast<TransformComponent*>(entitymanager.GetEntity(arrowentityID)->GetComponent(ComponentType::Transform));
		if (transformComponent)
		{
			transformComponent->position = VECTORMATH::Vector2D(100.0f, 100.0f); // Set the position as needed
			transformComponent->scaleX = 1.0f; // Set the scale as needed
			transformComponent->scaleY = 1.0f;
			transformComponent->rot = 0.0f; // Set the rotation as needed
		}

		// Add PhysicsComponent
		entitymanager.GetEntity(arrowentityID)->AddNewComponent(ComponentType::Physics);
		auto physicsComponent = dynamic_cast<PhysicsComponent*>(entitymanager.GetEntity(arrowentityID)->GetComponent(ComponentType::Physics));
		if (physicsComponent)
		{
			physicsComponent->velocity = VECTORMATH::Vector2D(10.0f, 0.0f); // Set the initial velocity as needed
		}

		// Add TextureComponent
		entitymanager.GetEntity(arrowentityID)->AddNewComponent(ComponentType::Texture);
		auto textureComponent = dynamic_cast<TextureComponent*>(entitymanager.GetEntity(arrowentityID)->GetComponent(ComponentType::Texture));
		if (textureComponent)
		{
			textureComponent->textureKey = { 1, 0 }; // Set the texture key as needed
		}

		entitymanager.GetEntity(arrowentityID)->AddNewComponent(ComponentType::Collision);
		auto collisionComponent = dynamic_cast<CollisionComponent*>(entitymanager.GetEntity(arrowentityID)->GetComponent(ComponentType::Collision));
		if (collisionComponent)
		{
			collisionComponent->c_Width = 20.0f; // Set the width as needed
			collisionComponent->c_Height = 10.0f; // Set the height as needed
		}
	}

	void AI_Arrow(ArrowPool& pool) {

		static double lastTime = glfwGetTime();
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		for (int i = 0; i < pool.activeSize; i++) {
			pool.activeArrow[i]->transform.position += pool.activeArrow[i]->direction * deltaTime * ARROW_SPEED;
			if (pool.activeArrow[i]->transform.position.x > ARROW_BOUNDARY_X) {
				Remove_Arrow(i, pool);
			}
			else if (pool.activeArrow[i]->transform.position.x < -ARROW_BOUNDARY_X) {
				Remove_Arrow(i, pool);
			}
			else if (pool.activeArrow[i]->transform.position.y > ARROW_BOUNDARY_Y) {
				Remove_Arrow(i, pool);
			}
			else if (pool.activeArrow[i]->transform.position.y < -ARROW_BOUNDARY_Y) {
				Remove_Arrow(i, pool);
			}
		}
	}

}