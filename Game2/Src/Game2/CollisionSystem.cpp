/******************************************************************************/
/*!
\file		Collision.cpp
\author		Ang Jun Sheng Aloysius, a.junshengaloysius@digipen.edu, 2201807 
\co		    Tristan Tham Rui Hong,  t.tham@digipen.edu 2200794

\date		01/03/2023
\brief		Contains the definitions for the collisionSystem class

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
		// Iterate through all pairs of entities
		for (auto it1 = entities->begin(); it1 != entities->end(); ++it1)
		{
			Entity* entity1 = it1->second.get();
		
			if (entity1->HasComponent(ComponentType::Collision) && (entity1->HasComponent(ComponentType::Transform)))
			{
				CollisionComponent* collisionComponent1 = dynamic_cast<CollisionComponent*>(entity1->GetComponent(ComponentType::Collision));
				TransformComponent* transformComponent1 = dynamic_cast<TransformComponent*>(entity1->GetComponent(ComponentType::Transform));
				
				AABB aabb1;

				if (collisionComponent1)
				{
					float halfWidth_1 = collisionComponent1->c_Width / 2.0f;
					float halfHeight_1 = collisionComponent1->c_Height / 2.0f;

					float minX_1 = static_cast<float>(transformComponent1->x) - halfWidth_1;
					float maxX_1 = static_cast<float>(transformComponent1->x) + halfWidth_1;
					float minY_1 = static_cast<float>(transformComponent1->y) - halfHeight_1;
					float maxY_1 = static_cast<float>(transformComponent1->y) + halfHeight_1;

					aabb1.min = VECTORMATH::Vec2(minX_1, minY_1);
					aabb1.max = VECTORMATH::Vec2(maxX_1, maxY_1);
				}

				VECTORMATH::Vec2 vel1 = VECTORMATH::Vec2(0.0f, 0.0f);

				for (auto it2 = std::next(it1); it2 != entities->end(); ++it2)
				{
					Entity* entity2 = it2->second.get();

					if (entity2->HasComponent(ComponentType::Collision) && (entity2->HasComponent(ComponentType::Transform)))
					{
						CollisionComponent* collisionComponent2 = dynamic_cast<CollisionComponent*>(entity2->GetComponent(ComponentType::Collision));
						TransformComponent* transformComponent2 = dynamic_cast<TransformComponent*>(entity2->GetComponent(ComponentType::Transform));

						AABB aabb2;

						float halfWidth_2  = collisionComponent2->c_Width  / 2.0f;
						float halfHeight_2 = collisionComponent2->c_Height / 2.0f;

						float minX_2 = static_cast<float>(transformComponent2->x) - halfWidth_2;
						float maxX_2 = static_cast<float>(transformComponent2->x) + halfWidth_2;
						float minY_2 = static_cast<float>(transformComponent2->y) - halfHeight_2;
						float maxY_2 = static_cast<float>(transformComponent2->y) + halfHeight_2;
						
						aabb2.min = VECTORMATH::Vec2(minX_2, minY_2);													
						aabb2.max = VECTORMATH::Vec2(maxX_2, maxY_2);
													
						VECTORMATH::Vec2 vel2 = VECTORMATH::Vec2(0.0f, 0.0f);

						// If collision detected, set the isColliding flag for both entities
						if (CollisionSystem::CollisionIntersection_RectRect(aabb1, vel1, aabb2, vel2))																			
						{
							if (collisionComponent1)
							{
								collisionComponent1->isColliding = true;
							}

							if (collisionComponent2)
							{
								collisionComponent2->isColliding = true;
							}
							std::cout << "Collision Detected between Entity" << static_cast<int>(entity1->GetID()) << " and Entity" << static_cast<int>(entity2->GetID()) <<std::endl;
						}
						else
						{
							if (collisionComponent1)
							{
								collisionComponent1->isColliding = false;
							}
							
							if (collisionComponent2)
							{
								collisionComponent2->isColliding = false;
							}

							std::cout << "No Collision Detected" << std::endl;
						}
					}
				}
				//update AABB coordinates in entity1
				if (collisionComponent1)
				{
					collisionComponent1->minX = static_cast<int>(aabb1.min.x);
					collisionComponent1->maxX = static_cast<int>(aabb1.max.x);
					collisionComponent1->minY = static_cast<int>(aabb1.min.y);
					collisionComponent1->maxY = static_cast<int>(aabb1.max.y);
				}
				
			}

		}
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
}
