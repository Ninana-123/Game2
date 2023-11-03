/******************************************************************************/
/*!
\file		CollisionSystem.cpp
\author		Ang Jun Sheng Aloysius, a.junshengaloysius@digipen.edu, 2201807 
\co		    Tristan Tham Rui Hong,  t.tham@digipen.edu 2200794

\date		10/09/2023
\brief		Contains the defintion for the logic of AABB, Circle to Circle and Circle to AABB Collision

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#include "pch.h"
#include "CollisionSystem.h"
#include "Entity.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"
#include "Input.h"


float dt = 0.0;  // Time difference between frames (delta time)

/*!*****************************************************************

  \brief
	  The logic of AABB collision.

  \param[in] aabb1
	  The bound of the first object.

  \param[in] vel1
	  The velocity of the first object.

  \param[in] aabb2
	  The bound of the second object.

  \param[in] vel2
	  The velocity of the second object.

  \return  boolean
	  Returns true if there is a collision, false is there is not.

********************************************************************/

namespace Engine
{
	
	void CollisionSystem::Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities)
	{
		//May want to process entities container here into smaller containers to send to relevant checks
		//Potential Conditional Collision check
		EntityToEntityCollision(entities);
		//potential EntityToMouseCollision
	}

	// Check if this object collides with another object
	bool CollisionSystem::CollisionIntersection_RectRect(const AABB& aabb1, const VECTORMATH::Vec2& vel1,
		const AABB& aabb2, const VECTORMATH::Vec2& vel2)
	{
		//UNREFERENCED_PARAMETER(aabb1);
		//UNREFERENCED_PARAMETER(vel1);
		//UNREFERENCED_PARAMETER(aabb2);
		//UNREFERENCED_PARAMETER(vel2);

		/*
		Implement the collision intersection over here.

		The steps are:
		Step 1: Check for collision detection between rectangles (assuming static here).
				If the check returns no overlap you continue with the following steps.

		Step 2: Initialize and calculate the new velocity of Vb
				tFirst = 0
				tLast = dt

		Step 3: Working with one dimension (x-axis).
				if(Vb < 0)
					case 1
					case 4
				if(Vb > 0)
					case 2
					case 3

				case 5

		Step 4: Repeat step 3 on the y-axis

		Step 5: Otherwise the rectangles intersect

		*/

		if (aabb1.max.x < aabb2.min.x)
			return false;
		if (aabb1.min.x > aabb2.max.x)
			return false;
		if (aabb1.max.y < aabb2.min.y)
			return false;
		if (aabb1.min.y > aabb2.max.y)
			return false;

		VECTORMATH::Vec2 relVelocity = { 0, 0 };
		VECTORMATH::Vec2 tFirst = { 0, 0 };
		VECTORMATH::Vec2 tLast = { dt, dt };
		VECTORMATH::Vec2 tTemp = { 0, 0 };
		relVelocity.x = vel2.x - vel1.x;
		relVelocity.y = vel2.y - vel1.y;

		// Checking for the X-axis
		// Case 1, B moving away from A towards the left (B moving left)
		if (relVelocity.x < 0) {
			if (aabb1.min.x > aabb2.max.x) {
				return false; // no collision as B moving away from A to the left
			}

			// Case 4, B moving towards A from the right
			else if (aabb1.max.x < aabb2.min.x) {
				tTemp.x = (aabb1.max.x - aabb2.min.x) / relVelocity.x;
				tFirst.x = tTemp.x > tFirst.x ? tTemp.x : tFirst.x;

			}
			else if (aabb1.min.x < aabb2.max.x) {
				tTemp.x = (aabb1.min.x - aabb2.max.x) / relVelocity.x;
				tLast.x = tTemp.x < tLast.x ? tTemp.x : tLast.x;
			}
		}

		// Case 2, B moving toward A from the left (B moving right)
		else if (relVelocity.x > 0) {
			if (aabb1.min.x > aabb2.max.x) {
				tTemp.x = (aabb1.min.x - aabb2.max.x) / relVelocity.x;
				tFirst.x = tTemp.x > tFirst.x ? tTemp.x : tFirst.x;
			}
			else if (aabb1.max.x > aabb2.min.x) {
				tTemp.x = (aabb1.max.x - aabb2.min.x) / relVelocity.x;
				tLast.x = tTemp.x < tLast.x ? tTemp.x : tLast.x;
			}

			// Case 3, B moving away from A towards the right
			else if (aabb1.max.x < aabb2.min.x) {
				return false; // no collision as B moving away from A to the right
			}
		}

		// Checking for the Y-axis 
		// Case 1, B moving away from A towards the bottom (B moving down)
		if (relVelocity.y < 0) {
			if (aabb1.min.y > aabb2.max.y) {
				return false; // no collision as B moving away from A to the bottom
			}

			// Case 4, B moving towards A from the top
			else if (aabb1.max.y < aabb2.min.y) {
				tTemp.y = (aabb1.max.y - aabb2.min.y) / relVelocity.y;
				tFirst.y = tTemp.y > tFirst.y ? tTemp.y : tFirst.y;

			}
			else if (aabb1.min.y < aabb2.max.y) {
				tTemp.y = (aabb1.min.y - aabb2.max.y) / relVelocity.y;
				tLast.y = tTemp.y < tLast.y ? tTemp.y : tLast.y;
			}
		}

		// Case 2, B moving toward A from the bottom (B moving up)
		else if (relVelocity.y > 0) {
			if (aabb1.min.y > aabb2.max.y) {
				tTemp.y = (aabb1.min.y - aabb2.max.y) / relVelocity.y;
				tFirst.y = tTemp.y > tFirst.y ? tTemp.y : tFirst.y;
			}

			else if (aabb1.max.y > aabb2.min.y) {
				tTemp.y = (aabb1.max.y - aabb2.min.y) / relVelocity.y;
				tLast.y = tTemp.y < tLast.y ? tTemp.y : tLast.y;
			}

			// Case 3, B moving away from A towards the top
			else if (aabb1.max.y < aabb2.min.y) {
				return false; // no collision as B moving away from A to the right
			}
		}

		// Case 5 
		if (tFirst.x > tLast.x || tFirst.y > tLast.y) {
			return false;
		}

		return true;
	}

	bool CollisionSystem::CollisionIntersection_PointRect(const VECTORMATH::Vec2& point, const AABB& aabb)
	{
		return (point.x >= aabb.min.x && point.x <= aabb.max.x && point.y >= aabb.min.y && point.y <= aabb.max.y);
	}

	// Function to check if two circles collide
	bool CollisionSystem::CollisionIntersection_CircleCircle(const Circle& circle1, const VECTORMATH::Vec2& vel1,
		const Circle& circle2, const VECTORMATH::Vec2& vel2)
	{
		// Calculate the relative velocity
		VECTORMATH::Vec2 relVelocity = vel2 - vel1;

		// Calculate the distance between the centers of the two circles
		VECTORMATH::Vec2 distanceVec = circle2.center - circle1.center;
		float distance = VECTORMATH::Vector2DLength(distanceVec);

		// Check if the distance is less than the sum of the radii
		if (distance > circle1.radius + circle2.radius) {
			// Circles are not colliding
			return false;
		}

		// If the circles are colliding, calculate the time of collision
		float tFirst = 0.0f;
		float tLast = 1.0f; // Assuming time interval [0, 1] for the frame

		// Calculate the components of relative velocity and distance along each axis
		float relVelX = relVelocity.x;
		float relVelY = relVelocity.y;
		float distX = distanceVec.x;
		float distY = distanceVec.y;

		// Calculate the quadratic coefficients
		float a = relVelX * relVelX + relVelY * relVelY;
		float b = 2.0f * (relVelX * distX + relVelY * distY);
		float c = distX * distX + distY * distY - (circle1.radius + circle2.radius) * (circle1.radius + circle2.radius);

		// Check for a collision along the x-axis
		if (a != 0.0f) {
			float discriminant = b * b - 4.0f * a * c;
			if (discriminant >= 0.0f) {
				float sqrtDiscriminant = sqrt(discriminant);
				float t1 = (-b + sqrtDiscriminant) / (2.0f * a);
				float t2 = (-b - sqrtDiscriminant) / (2.0f * a);

				// Update tFirst and tLast based on collision times along the x-axis
				if (t1 > t2) {
					float temp = t1;
					t1 = t2;
					t2 = temp;
				}

				if (t1 > tFirst) {
					tFirst = t1;
				}

				if (t2 < tLast) {
					tLast = t2;
				}

				// If tFirst is greater than tLast, there is no collision along the x-axis
				if (tFirst > tLast) {
					return false;
				}
			}
		}

		// Check for a collision along the y-axis
		if (a != 0.0f) {
			float discriminant = b * b - 4.0f * a * c;
			if (discriminant >= 0.0f) {
				float sqrtDiscriminant = sqrt(discriminant);
				float t1 = (-b + sqrtDiscriminant) / (2.0f * a);
				float t2 = (-b - sqrtDiscriminant) / (2.0f * a);

				// Update tFirst and tLast based on collision times along the y-axis
				if (t1 > t2) {
					float temp = t1;
					t1 = t2;
					t2 = temp;
				}

				if (t1 > tFirst) {
					tFirst = t1;
				}

				if (t2 < tLast) {
					tLast = t2;
				}

				// If tFirst is greater than tLast, there is no collision along the y-axis
				if (tFirst > tLast) {
					return false;
				}
			}
		}

		// If tFirst is less than or equal to 1, a collision occurs within the time frame
		if (tFirst <= 1.0f) {
			return true;
		}

		return false;
	}

	// Function to check if a circle and a rectangle collide
	bool CollisionSystem::CollisionIntersection_CircleRect(const Circle& circle, const AABB& rect) {
		float testX = circle.center.x;
		float testY = circle.center.y;

		// Calculate the closest point on the rectangle to the circle's center
		if (circle.center.x < rect.min.x) {
			testX = rect.min.x;
		}
		else if (circle.center.x > rect.max.x) {
			testX = rect.max.x;
		}

		if (circle.center.y < rect.min.y) {
			testY = rect.min.y;
		}
		else if (circle.center.y > rect.max.y) {
			testY = rect.max.y;
		}

		// Calculate the horizontal and vertical distances
		float distanceX = circle.center.x - testX;
		float distanceY = circle.center.y - testY;

		// Calculate the distance from the circle's center to the closest point on the rectangle
		float distance = std::sqrt(distanceX * distanceX + distanceY * distanceY);

		// Check for collision
		if (distance < circle.radius) {
			return true; // Collision
		}
		else {
			return false; // No collision
		}
	}

	// Function to check if the area is being touched/clicked
	bool CollisionSystem::IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
	{
		if (click_x > area_center_x - (area_width / 2) && click_x < area_center_x + (area_width / 2)
			&& click_y < area_center_y + (area_height / 2) && click_y > area_center_y - (area_height / 2))
		{
			return true;
		}

		return false ;
	}

	void CollisionSystem::EntityToEntityCollision(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities)
	{
		// Iterate through all pairs of entities
		for (auto it1 = entities->begin(); it1 != entities->end(); ++it1)
		{
			Entity* entity1 = it1->second.get();

			if (entity1->HasComponent(ComponentType::Collision) && (entity1->HasComponent(ComponentType::Transform)))
			{
				CollisionComponent* collisionComponent1 = dynamic_cast<CollisionComponent*>(entity1->GetComponent(ComponentType::Collision));
				TransformComponent* transformComponent1 = dynamic_cast<TransformComponent*>(entity1->GetComponent(ComponentType::Transform));

				AABB aabb1;
				Circle circle1;
				circle1.center = VECTORMATH::Vec2(transformComponent1->position.x, transformComponent1->position.y);
				circle1.radius = 0.f;
				VECTORMATH::Vec2 vel1;

				Input::GetMousePosition();
				if (IsAreaClicked(transformComponent1->position.x + 640.f, 360.f - transformComponent1->position.y, 
					collisionComponent1->c_Width, collisionComponent1->c_Height, Input::GetMouseX(), Input::GetMouseY())) {
					std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl;
				}

				if (collisionComponent1)
				{				
					aabb1 = collisionComponent1->aabb;
					// circle1 = meow;
				}

				if (entity1->HasComponent(ComponentType::Physics))
				{
					PhysicsComponent* physicsComponent1 = dynamic_cast<PhysicsComponent*>(entity1->GetComponent(ComponentType::Physics));
					vel1 = VECTORMATH::Vec2(physicsComponent1->velocity.x, physicsComponent1->velocity.y);
				}
				else
				{
					vel1 = VECTORMATH::Vec2(0.0f, 0.0f);
				}

				bool isColliding = false; // Flag to check if entity1 is colliding with any other entity

				for (auto it2 = entities->begin(); it2 != entities->end(); ++it2)
				{
					if (it1 != it2) // Avoid self-collision check
					{
						Entity* entity2 = it2->second.get();

						if (entity2->HasComponent(ComponentType::Collision) && (entity2->HasComponent(ComponentType::Transform)))
						{
							CollisionComponent* collisionComponent2 = dynamic_cast<CollisionComponent*>(entity2->GetComponent(ComponentType::Collision));
							//TransformComponent* transformComponent2 = dynamic_cast<TransformComponent*>(entity2->GetComponent(ComponentType::Transform));

							AABB aabb2;
							Circle circle2;
							circle2.center = VECTORMATH::Vec2(435, 60);
							circle2.radius = 0.f;
							VECTORMATH::Vec2 vel2;
							
							if (collisionComponent2)
							{
								aabb2 = collisionComponent2->aabb;
							}
											
							if (entity2->HasComponent(ComponentType::Physics))
							{
								PhysicsComponent* physicsComponent2 = dynamic_cast<PhysicsComponent*>(entity2->GetComponent(ComponentType::Physics));
								vel2 = VECTORMATH::Vec2(physicsComponent2->velocity.x, physicsComponent2->velocity.y);
							}
							else
							{
								vel2 = VECTORMATH::Vec2(0.0f, 0.0f);
							}
							// Check for collision with entity2
							if (CollisionSystem::CollisionIntersection_RectRect(aabb1, vel1, aabb2, vel2))
							{
								isColliding = true;
								std::cout << "Collision Detected between Entity" << static_cast<int>(entity1->GetID()) << " and Entity" << static_cast<int>(entity2->GetID()) << std::endl;
							}

							if (CollisionSystem::CollisionIntersection_CircleCircle(circle1, vel1, circle2, vel2)) {
								//isColliding = true;
								std::cout << "Circle Collision Detected between Entity" << static_cast<int>(entity1->GetID()) << " and Entity" << static_cast<int>(entity2->GetID()) << std::endl;
							}

						}
					}
				}

				// Set the collision flag based on whether there was any collision
				if (collisionComponent1)
				{
					collisionComponent1->isColliding = isColliding;
				}

				if (!isColliding)
				{
					//std::cout << "No Collision Detected for Entity" << static_cast<int>(entity1->GetID()) << std::endl;
					//std::cout << Input::GetMouseX() << std::endl;
					//std::cout << Input::GetMouseY() << std::endl;
				}

				//update AABB coordinates in entity1
				if (collisionComponent1)
				{
					float halfWidth_1 = collisionComponent1->c_Width / 2.0f;
					float halfHeight_1 = collisionComponent1->c_Height / 2.0f;

					float minX_1 = static_cast<float>(transformComponent1->position.x) - halfWidth_1;
					float maxX_1 = static_cast<float>(transformComponent1->position.x) + halfWidth_1;
					float minY_1 = static_cast<float>(transformComponent1->position.y) - halfHeight_1;
					float maxY_1 = static_cast<float>(transformComponent1->position.y) + halfHeight_1;

					collisionComponent1->aabb.min = VECTORMATH::Vec2(minX_1, minY_1);
					collisionComponent1->aabb.max = VECTORMATH::Vec2(maxX_1, maxY_1);		

				}

	
			}
		}
	}
}
