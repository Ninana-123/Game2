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
#include "ShootingSystem.h"
#include "PhysicsComponent.h"
#include "Input.h"
#include "Window.h"
#include "inGameGUI.h"
#include "GraphicsSystem.h"
#include "AudioEngine.h"
#include "AssetManager.h"

double l_dt = 0.0;  // Time difference between frames (delta time)
bool buttonCollision = false;
int lastCollidingEntity = 0;
int lastCollidingEntityTexture = 0;
int towerCollidingEntity = 0;
int tower2CollidingEntity = 0;
int tower1CollidingEntityHealth = 0;
int tower2CollidingEntityHealth = 0;
int castleCollidingEntityHealth = 0;
int victoryID = 0;
int defeatID = 0;
int lemaoArrowID = 0;
int unitID = 0;
bool tower1Destroyed = false;
bool tower2Destroyed = false;
bool castleDestroyed = false;
bool isStartingPoint = true;
bool towerCollision = false;
bool isSpawned = false;
bool unitHalfSpawned = false;
bool isShooting = false;
bool unitArrowCollision = false;
bool infantrySpawned = false;
bool tankSpawned = false;
bool archerSpawned = false;
bool arrowSpawnedByArcher = false;
bool accessedTower1 = false;
bool accessedTower2 = false;
bool arrowAccessedCastle = false;
bool infantryDead = false;
bool tankDead = false;
bool archerDead = false;
float towerHealth = 0.0f;
std::vector<Engine::Stats> towers;

float currentWidth = 0, currentHeight = 0;
float aspectRatioWidth = 0, aspectRatioHeight = 0;



// Define a map for towerCollidingEntityHealth and corresponding texture keys
std::map<int, int> towerHealthToTextureKey = 
{
	{0, 32},
	{5, 33},
	{10, 34},
	{15, 35},
	{20, 36},
	{25, 37},
	{35, 38},
	{45, 39},
	{55, 40},
	{65, 41}
};

std::map<int, int> castleHealthToTextureKey =
{
	{0, 32},
	{10, 33},
	{20, 34},
	{30, 35},
	{40, 36},
	{50, 37},
	{60, 38},
	{70, 39},
	{80, 40},
	{90, 41}
};

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
	Input inputManager;

	void CollisionSystem::Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities)

	{
		/*
		// Separate entities based on layers
		std::unordered_map<EntityID, std::unique_ptr<Entity>> worldLayerEntities;
		std::unordered_map<EntityID, std::unique_ptr<Entity>> editableLayerEntities;

		// Temporary vector to hold entities to be moved
		std::vector<std::unordered_map<EntityID, std::unique_ptr<Entity>>::iterator> entitiesToMove;

		// Move entities to separate containers based on layers
		for (auto it = entities->begin(); it != entities->end(); ++it)
		{
			Entity* entity = it->second.get();

			if (entity->HasComponent(ComponentType::Collision))
			{
				CollisionComponent* collisionComponent = dynamic_cast<CollisionComponent*>(entity->GetComponent(ComponentType::Collision));

				switch (collisionComponent->layer)
				{
				case Layer::World:
					worldLayerEntities[it->first] = std::move(it->second);
					entitiesToMove.push_back(it); // Add iterator to the list
					break;

				case Layer::Editable:
					editableLayerEntities[it->first] = std::move(it->second);
					entitiesToMove.push_back(it); // Add iterator to the list
					break;

				default:
					break;
				}
			}
		}

		// Remove moved entities from the original container
		for (auto& it : entitiesToMove)
		{
			entities->erase(it);
		}

		// Perform collision checks for world layer entities
		EntityToEntityCollision(&worldLayerEntities);

		// Perform collision checks for editable layer entities
		EntityToMouseCollision(&editableLayerEntities);

		// Move entities back to the original container
		for (auto& entityPair : worldLayerEntities)
		{
			entities->emplace(std::move(entityPair));
		}

		for (auto& entityPair : editableLayerEntities)
		{
			entities->emplace(std::move(entityPair));
		}

		*/
		EntityToMouseCollision(entities);
		EntityToEntityCollision(entities);


	}

	EntityID CollisionSystem::GetLastCollidingEntityID() { return lastCollidingEntityID; }

	// Check if this object collides with another object
	bool CollisionSystem::CollisionIntersection_RectRect(const AABB& aabb1, const VECTORMATH::Vec2& vel1,
		const AABB& aabb2, const VECTORMATH::Vec2& vel2)
	{
		if (aabb1.max.x < aabb2.min.x)
			return false;
		if (aabb1.min.x > aabb2.max.x)
			return false;
		if (aabb1.max.y < aabb2.min.y)
			return false;
		if (aabb1.min.y > aabb2.max.y)
			return false;
		l_dt = dt;
		VECTORMATH::Vec2 relVelocity = { 0, 0 };
		VECTORMATH::Vec2 tFirst = { 0, 0 };
		VECTORMATH::Vec2 tLast = { static_cast<float>(dt) , static_cast<float>(dt) };
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

	std::string CollisionSystem::returnSystem()
	{
		return "collisionSystem";
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

	// Function to project a polygon onto an axis (edge normal)
	void CollisionSystem::ProjectPolygon(const std::vector<VECTORMATH::Vec2>& polygon, const VECTORMATH::Vec2& axis, float& min, float& max) {
		min = max = Vector2DDotProduct(polygon[0], axis);
		for (size_t i = 1; i < polygon.size(); i++) {
			float dot = Vector2DDotProduct(polygon[i], axis);
			if (dot < min) {
				min = dot;
			}
			if (dot > max) {
				max = dot;
			}
		}
	}

	// Function to check for intersection between two convex polygons using the SAT
	bool CollisionSystem::PolygonIntersectionSAT(const std::vector<VECTORMATH::Vec2>& polygon1, const std::vector<VECTORMATH::Vec2>& polygon2,
		float rotationAngle1, float rotationAngle2) {
		// Create rotated copies of the input polygons
		std::vector<VECTORMATH::Vec2> rotatedPolygon1, rotatedPolygon2;

		// Rotate and update the vertices of polygon1
		for (const VECTORMATH::Vec2& vertex : polygon1) {
			VECTORMATH::Vec2 rotatedVertex = vertex; // Copy the vertex
			rotateVector2D(rotatedVertex, rotationAngle1); // Call the member function on the copied vertex
			rotatedPolygon1.push_back(rotatedVertex); // Add the rotated vertex to the rotated polygon
		}

		// Rotate and update the vertices of polygon2
		for (const VECTORMATH::Vec2& vertex : polygon2) {
			VECTORMATH::Vec2 rotatedVertex = vertex; // Copy the vertex
			rotateVector2D(rotatedVertex, rotationAngle2); // Rotate the copied vertex
			rotatedPolygon2.push_back(rotatedVertex); // Add the rotated vertex to the rotated polygon
		}

		// Calculate the edges and normals for both rotated polygons
		std::vector<Edge> edges1, edges2;
		for (size_t i = 0; i < rotatedPolygon1.size(); i++) {
			size_t j = (i + 1) % rotatedPolygon1.size();
			VECTORMATH::Vec2 edge = rotatedPolygon1[j] - rotatedPolygon1[i];
			VECTORMATH::Vec2 normal = edge; // No need to normalize here
			Edge e;
			e.normal = normal;
			ProjectPolygon(rotatedPolygon1, normal, e.min, e.max);
			edges1.push_back(e);
		}
		for (size_t i = 0; i < rotatedPolygon2.size(); i++) {
			size_t j = (i + 1) % rotatedPolygon2.size();
			VECTORMATH::Vec2 edge = rotatedPolygon2[j] - rotatedPolygon2[i];
			VECTORMATH::Vec2 normal = edge; // No need to normalize here
			Edge e;
			e.normal = normal;
			ProjectPolygon(rotatedPolygon2, normal, e.min, e.max);
			edges2.push_back(e);
		}

		// Test for separation along each axis (edge normal)
		for (const Edge& edge : edges1) {
			float min1, max1, min2, max2;
			ProjectPolygon(rotatedPolygon1, edge.normal, min1, max1);
			ProjectPolygon(rotatedPolygon2, edge.normal, min2, max2);
			if (max1 < min2 || max2 < min1) {
				// There is separation, no intersection
				return false;
			}
		}
		for (const Edge& edge : edges2) {
			float min1, max1, min2, max2;
			ProjectPolygon(rotatedPolygon1, edge.normal, min1, max1);
			ProjectPolygon(rotatedPolygon2, edge.normal, min2, max2);
			if (max1 < min2 || max2 < min1) {
				// There is separation, no intersection
				return false;
			}
		}

		// If no separation occurs along any axis, there is intersection
		return true;
	}

	// Function to check if the area is being touched/clicked
	bool CollisionSystem::IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
	{
		if (click_x > area_center_x - (area_width / 2) && click_x < area_center_x + (area_width / 2)
			&& click_y < area_center_y + (area_height / 2) && click_y > area_center_y - (area_height / 2))
		{
			return true;
		}

		return false;
	}

	void CollisionSystem::PlayerTowerCollision(EntityID lhs, EntityID rhs)
	{
		CollisionQueue.emplace(std::make_pair(lhs, rhs));
	}

	void CollisionSystem::ArcherTowerCollision(EntityID lhs, EntityID rhs)
	{
		ArcherCollisionQueue.emplace(std::make_pair(lhs, rhs));
	}

	//void CollisionSystem::PlayerArrowCollision(EntityID lhs, EntityID rhs)
	//{
	//	PlayerArrowQueue.emplace(std::make_pair(lhs, rhs));
	//}

	void CollisionSystem::EntityToEntityCollision(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities)
	{
		// Iterate through all pairs of entities
		for (auto it1 = entities->begin(); it1 != entities->end(); ++it1)
		{
			Entity* entity1 = it1->second.get();

			if (entity1->HasComponent(ComponentType::Transform) && entity1->HasComponent(ComponentType::Collision))
			{
				CollisionComponent* collisionComponent1 = dynamic_cast<CollisionComponent*>(entity1->GetComponent(ComponentType::Collision));
				TransformComponent* transformComponent1 = dynamic_cast<TransformComponent*>(entity1->GetComponent(ComponentType::Transform));
				StatsComponent* statsComponent1 = dynamic_cast<StatsComponent*>(entity1->GetComponent(ComponentType::Stats));
				TextureComponent* textureComponent = dynamic_cast<TextureComponent*>(entity1->GetComponent(ComponentType::Texture));


				//// Workaround to add components as prefabs are not saving
				//if (textureComponent)
				//{
				//	if (!(entity1->HasComponent(ComponentType::Stats)) && textureComponent->textureKey.mainIndex == 2)
				//	{
				//		entity1->AddNewComponent(ComponentType::Stats);
				//		std::cout << "stats component added to tank" << std::endl;

				//	}

				//	if (!(entity1->HasComponent(ComponentType::Stats)) && textureComponent->textureKey.mainIndex == 3)
				//	{
				//		entity1->AddNewComponent(ComponentType::Stats);
				//		std::cout << "stats component added to archer" << std::endl;
				//	}

				//	if (statsComponent1 && textureComponent->textureKey.mainIndex == 2)
				//	{
				//		if (!statsComponent1->tankStatsSet) 
				//		{
				//			statsComponent1->health = 80;
				//			std::cout << "health added to tank" << std::endl;
				//			statsComponent1->tankStatsSet = true;
				//		}
				//	}

				//	if (statsComponent1 && textureComponent->textureKey.mainIndex == 3)
				//	{
				//		if (!statsComponent1->archerStatsSet) 
				//		{
				//			statsComponent1->health = 50;
				//			std::cout << "health added to archer" << std::endl;
				//			statsComponent1->archerStatsSet = true;
				//		}
				//	}
				//}

				

				if (collisionComponent1 && collisionComponent1->disableCollision)
				{
					continue;
				}

				if (collisionComponent1 != nullptr && collisionComponent1->layer != Layer::inGameGUI && 
					collisionComponent1->layer != Layer::Editable && collisionComponent1->layer != Layer::BeforeSpawn)
				{
					AABB aabb1;
					Circle circle1;
					circle1.center = VECTORMATH::Vec2(transformComponent1->position.x, transformComponent1->position.y);
					VECTORMATH::Vec2 vel1;
					VECTORMATH::Vec2 circleVel1 = VECTORMATH::Vec2(collisionComponent1->collisionVel.x, collisionComponent1->collisionVel.y);


					// Set tower's circle radius
					if (collisionComponent1->layer == Layer::Tower && statsComponent1)
					{
						// statsComponent1->range = 100;
						circle1.radius = statsComponent1->range;
					}

					if (collisionComponent1)
					{
						aabb1 = collisionComponent1->aabb;
					}

					if (entity1->HasComponent(ComponentType::Physics))
					{
						//PhysicsComponent* physicsComponent1 = dynamic_cast<PhysicsComponent*>(entity1->GetComponent(ComponentType::Physics));
						//vel1 = VECTORMATH::Vec2(physicsComponent1->velocity.x, physicsComponent1->velocity.y);
						vel1 = VECTORMATH::Vec2(transformComponent1->position.x, transformComponent1->position.y);
					}
					else
					{
						vel1 = VECTORMATH::Vec2(transformComponent1->position.x, transformComponent1->position.y);
					}

					bool isColliding = false; // Flag to check if entity1 is colliding with any other entity

					for (auto it2 = entities->begin(); it2 != entities->end(); ++it2)
					{
						if (it1 != it2) // Avoid self-collision check
						{
							Entity* entity2 = it2->second.get();
							//if ((entity1->GetID() == 13 && entity2->GetID() == 15)
							//	|| (entity1->GetID() == 15 && entity2->GetID() == 13)) // Defo wrong, should check with entity types instead
							//{
							//	PlayerArrowCollision(entity1->GetID(), entity2->GetID());
							//}

							if (entity2->HasComponent(ComponentType::Transform))
							{
								CollisionComponent* collisionComponent2 = dynamic_cast<CollisionComponent*>(entity2->GetComponent(ComponentType::Collision));
								TransformComponent* transformComponent2 = dynamic_cast<TransformComponent*>(entity2->GetComponent(ComponentType::Transform));
								StatsComponent* statsComponent2 = dynamic_cast<StatsComponent*>(entity2->GetComponent(ComponentType::Stats));
								TextureComponent* textureComponent2 = dynamic_cast<TextureComponent*>(entity2->GetComponent(ComponentType::Texture));
								ShootingComponent* shootingComponent1 = dynamic_cast<ShootingComponent*>(entity2->GetComponent(ComponentType::Shooting));

								if (collisionComponent2 && collisionComponent2->disableCollision == true)
								{
									continue;
								}

								AABB aabb2;
								Circle circle2;
								circle2.center = VECTORMATH::Vec2(transformComponent2->position.x, transformComponent2->position.y);

								VECTORMATH::Vec2 vel2;
								VECTORMATH::Vec2 circleVel2;

								//if ((entity1->HasComponent(ComponentType::Logic) && entity2->HasComponent(ComponentType::Physics))
								//	|| (entity1->HasComponent(ComponentType::Physics) && entity2->HasComponent(ComponentType::Logic)))
								//{
								//	PlayerArrowCollision(entity1->GetID(), entity2->GetID());
								//}

								if (statsComponent2)
								{
									statsComponent2->range = 100;
									circle2.radius = statsComponent2->range;
								}

								// Getting the health of each tower/castle
								if (collisionComponent2)
								{
									aabb2 = collisionComponent2->aabb;
									
									if (statsComponent2) // Check if statsComponent2 is not nullptr
									{
										if (entity2->GetID() == 7)
										{
											tower2CollidingEntityHealth = static_cast<int>(statsComponent2->health);
										}
										if (entity2->GetID() == 8)
										{
											tower1CollidingEntityHealth = static_cast<int>(statsComponent2->health);
										}
										if (entity2->GetID() == 9)
										{
											castleCollidingEntityHealth = static_cast<int>(statsComponent2->health);
										}
									}
								}

								if (entity2->HasComponent(ComponentType::Physics))
								{
									//PhysicsComponent* physicsComponent2 = dynamic_cast<PhysicsComponent*>(entity2->GetComponent(ComponentType::Physics));
									//vel2 = VECTORMATH::Vec2(physicsComponent2->velocity.x, physicsComponent2->velocity.y);
									vel2 = VECTORMATH::Vec2(transformComponent2->position.x, transformComponent2->position.y);
								}
								else
								{
									vel2 = VECTORMATH::Vec2(transformComponent2->position.x, transformComponent2->position.y);
								}

								// Add health back to 0 so that the texture will update
								if (tower1CollidingEntityHealth < 0) 
								{
									tower1CollidingEntityHealth++;
								}

								if (tower2CollidingEntityHealth < 0)
								{
									tower2CollidingEntityHealth++;
								}

								if (castleCollidingEntityHealth < 0)
								{
									castleCollidingEntityHealth++;
								}

								// Changing the texture for the healthbars
								if (entity2->GetID() == 11 && towerCollidingEntity == 8)
								{
									// Find the corresponding texture key for the towerCollidingEntityHealth
									auto it = towerHealthToTextureKey.find(tower1CollidingEntityHealth);
									// If found, set the texture key
									if (it != towerHealthToTextureKey.end())
									{
										textureComponent2->textureKey = { it->second, 0 };
									}
								}

								if (entity2->GetID() == 10 && towerCollidingEntity == 7)
								{
									// Find the corresponding texture key for the towerCollidingEntityHealth
									auto it = towerHealthToTextureKey.find(tower2CollidingEntityHealth);
									// If found, set the texture key
									if (it != towerHealthToTextureKey.end())
									{
										textureComponent2->textureKey = { it->second, 0 };
									}
								}

								if (entity2->GetID() == 12 && towerCollidingEntity == 9)
								{
									// Find the corresponding texture key for the towerCollidingEntityHealth
									auto it = castleHealthToTextureKey.find(castleCollidingEntityHealth);
									// If found, set the texture key
									if (it != castleHealthToTextureKey.end())
									{
										textureComponent2->textureKey = { it->second, 0 };
									}
								}

								// Getting ID of victory screen
								if (textureComponent2->textureKey.mainIndex == 21)
								{
									victoryID = entity2->GetID();
								}

								// Getting ID of defeat screen
								if (textureComponent2->textureKey.mainIndex == 53)
								{
									defeatID = entity2->GetID();
								}

								// Check for collision with entity2
								if (entity2->HasComponent(ComponentType::Collision))
								{

									if (collisionComponent2 != nullptr)
									{
										circleVel2 = VECTORMATH::Vec2(collisionComponent2->collisionVel.x, collisionComponent2->collisionVel.y);
										BehaviourComponent* behaviourComponent1 = dynamic_cast<BehaviourComponent*>(entity1->GetComponent(ComponentType::Logic));

										if (CollisionSystem::CollisionIntersection_RectRect(aabb1, vel1, aabb2, vel2)
											&& collisionComponent2->layer != Layer::inGameGUI)
										{
											isColliding = true;

											// Collision from arrow to unit
											if (collisionComponent2->layer == Layer::Arrow && collisionComponent2->layerTarget == Layer::World && collisionComponent1->layer == Layer::World)
											{
												// std::cout << "outside behavior" << std::endl;
												if (behaviourComponent1) 
												{
													//std::cout << "inside behavior" << std::endl;
													unitArrowCollision = true;
													lemaoArrowID = entity2->GetID();
													statsComponent1->health -= 5;
													std::cout << "unit's health is: " << statsComponent1->health << std::endl;
													if (statsComponent1->health <= 0) 
													{
														std::cout << "unit is dead" << std::endl;
														statsComponent1->playerDead = true;

														if (statsComponent1->playerDead) 
														{
															// Check to see which unit actually died
															if (textureComponent->textureKey.mainIndex == 1)
															{
																infantryDead = true;
																statsComponent1->infantryDead = true;
																infantryDead = statsComponent1->infantryDead;
																textureComponent->textureKey = { 1, 3 };
																behaviourComponent1->SetBehaviourState(c_state::Death);

															}
															if (textureComponent->textureKey.mainIndex == 2)
															{
																tankDead = true;
																statsComponent1->tankDead = true;
																tankDead = statsComponent1->tankDead;
																//textureComponent->textureKey = { 2, 3 };
																behaviourComponent1->SetBehaviourState(c_state::Death);
															}
															if (textureComponent->textureKey.mainIndex == 3)
															{
																archerDead = true;
																statsComponent1->archerDead = true;
																archerDead = statsComponent1->archerDead;
																//textureComponent->textureKey = { 3, 3 };
																behaviourComponent1->SetBehaviourState(c_state::Death);
															}
														}
													}
												}
											}

											if (collisionComponent2->layer == Layer::Arrow && collisionComponent2->layerTarget == Layer::Tower && collisionComponent1->layer == Layer::Tower)
											{
												unitArrowCollision = true;
												lemaoArrowID = entity2->GetID();
											}

											//Collision Between Non Tower and Towers only -bc Tower can never AABB collide with another Tower
											if (collisionComponent2->layer == Layer::Tower)
											{
												towerCollision = true;
												buttonCollision = true;

												if (behaviourComponent1)
												{
													behaviourComponent1->SetBehaviourState(c_state::Attack);
													collisionComponent1->target = entity2;
													towerCollidingEntity = entity2->GetID();
													// towerCollidingEntityHealth = statsComponent2->health;
													if (entity2->GetID() == 7)
													{
														//tower2CollidingEntityHealth = statsComponent2->health;
														if (tower2CollidingEntityHealth <= 0)
														{
															tower2Destroyed = true;
															isColliding = false;
														
														}
														if ((textureComponent2->textureKey.mainIndex == 4 && textureComponent2->textureKey.subIndex == 0)
															&& tower2Destroyed == true)
														{
															textureComponent2->textureKey = { 4, 4 };
														}
													}
													if (entity2->GetID() == 8)
													{
														//tower1CollidingEntityHealth = statsComponent2->health;
														if (tower1CollidingEntityHealth <= 0)
														{
															tower1Destroyed = true;
															isColliding = false;
														}
														if ((textureComponent2->textureKey.mainIndex == 4 && textureComponent2->textureKey.subIndex == 0)
															&& tower1Destroyed == true)
														{
															textureComponent2->textureKey = { 4, 4 };
															
															
														}
														// std::cout << "Tower 2 health: " << tower2CollidingEntityHealth << std::endl;
													}
													if (entity2->GetID() == 9)
													{
														//tower1CollidingEntityHealth = statsComponent2->health;
														if (castleCollidingEntityHealth <= 0)
														{
															castleDestroyed = true;
															isGameOver = true;
															isColliding = false;
														}
														if ((textureComponent2->textureKey.mainIndex == 5 && textureComponent2->textureKey.subIndex == 0)
															&& castleDestroyed == true)
														{
															textureComponent2->textureKey = { 5, 5 };
														}
														// std::cout << "Tower 2 health: " << tower2CollidingEntityHealth << std::endl;
													}

													// std::cout << "Collision Detected between Entity" << static_cast<int>(entity1->GetID()) << " and Entity" << static_cast<int>(entity2->GetID()) << std::endl;
												}
											}
										}

										// std::cout << "Circle Vel1 is: " << circleVel1.x << " " << circleVel1.y << "\n" << "Circle vel2 is: " << circleVel2.x << " " << circleVel2.y << std::endl;

										// Check if tower radius is colliding with the player's radius
										if (CollisionSystem::CollisionIntersection_CircleCircle(circle1, circleVel1, circle2, circleVel2)
											&& collisionComponent2->layer != Layer::inGameGUI 
											&& collisionComponent1->layer == Layer::Tower)
										{

											//isColliding = true;
											if (collisionComponent2->layer == Layer::World) 
											{
												isShooting = true;
												PlayerTowerCollision(entity1->GetID(), entity2->GetID());
												if (!tower1Destroyed && !tower2Destroyed && !castleDestroyed)
												{
													//std::cout << "goes into first feed" << std::endl;
													PlayerTowerCollision(entity1->GetID(), entity2->GetID());
												}
												if (tower1Destroyed && !tower2Destroyed)
												{
													//std::cout << "goes into second feed" << std::endl;
													while (!CollisionQueue.empty())
													{
														CollisionQueue.pop();
													}
													while (!collisionComponent2->PlayerTowerVector.empty())
													{
														collisionComponent2->PlayerTowerVector.clear();
													}
													PlayerTowerCollision(7, entity2->GetID());
												}
												if (tower2Destroyed && !tower1Destroyed)
												{
													//std::cout << "goes into third feed" << std::endl;
													while (!CollisionQueue.empty())
													{
														CollisionQueue.pop();
													}
													while (!collisionComponent2->PlayerTowerVector.empty())
													{
														collisionComponent2->PlayerTowerVector.clear();
													}
													PlayerTowerCollision(8, entity2->GetID());
												}
												if (tower1Destroyed && tower2Destroyed)
												{
													//std::cout << "goes into fourth feed" << std::endl;
													while (!CollisionQueue.empty())
													{
														CollisionQueue.pop();
													}
													while (!collisionComponent2->PlayerTowerVector.empty())
													{
														collisionComponent2->PlayerTowerVector.clear();
													}
													PlayerTowerCollision(9, entity2->GetID());
												}
												collisionComponent1->PlayerTowerQueue = CollisionQueue;
												
												while (!collisionComponent1->PlayerTowerQueue.empty())
												{
												    collisionComponent1->PlayerTowerVector.push_back(collisionComponent1->PlayerTowerQueue.front());
												    collisionComponent1->PlayerTowerQueue.pop();
												}

												collisionComponent1->towerShooting = true;


												if (textureComponent2->textureKey.mainIndex == 3) 
												{
													// Reset the vector once one tower dies so that the arrow shoots correctly
													if (!tower1Destroyed && !tower2Destroyed && !castleDestroyed)
													{
														//std::cout << "goes into first feed" << std::endl;
														ArcherTowerCollision(entity1->GetID(), entity2->GetID());
													}
													if (tower1Destroyed && !accessedTower2)
													{
														//std::cout << "goes into second feed" << std::endl;
														while (!ArcherCollisionQueue.empty()) 
														{
															ArcherCollisionQueue.pop();
														}
														while (!collisionComponent2->ArcherTowerVector.empty())
														{
															collisionComponent2->ArcherTowerVector.clear();
														}
														ArcherTowerCollision(7, entity2->GetID());
														accessedTower2 = true;
													}
													if (tower2Destroyed && !accessedTower1)
													{
														//std::cout << "goes into third feed" << std::endl;
														while (!ArcherCollisionQueue.empty())
														{
															ArcherCollisionQueue.pop();
														}
														while (!collisionComponent2->ArcherTowerVector.empty())
														{
															collisionComponent2->ArcherTowerVector.clear();
														}
														ArcherTowerCollision(8, entity2->GetID());
														accessedTower1 = true;
													}
													if (tower1Destroyed && tower2Destroyed && !arrowAccessedCastle)
													{
														//std::cout << "goes into fourth feed" << std::endl;
														while (!ArcherCollisionQueue.empty())
														{
															ArcherCollisionQueue.pop();
														}
														while (!collisionComponent2->ArcherTowerVector.empty())
														{
															collisionComponent2->ArcherTowerVector.clear();
														}
														ArcherTowerCollision(9, entity2->GetID());
														arrowAccessedCastle = true;
													}
													collisionComponent2->ArcherTowerQueue = ArcherCollisionQueue;

													while (!collisionComponent2->ArcherTowerQueue.empty())
													{
														collisionComponent2->ArcherTowerVector.push_back(collisionComponent2->ArcherTowerQueue.front());
														collisionComponent2->ArcherTowerQueue.pop();
													}

													// Code for archer to stop/start shooting
													if (!tower1Destroyed || !tower2Destroyed || !castleDestroyed) 
													{
														collisionComponent2->archerShooting = true;
													}
													if (tower1Destroyed && tower2Destroyed && castleDestroyed) 
													{
														collisionComponent2->archerShooting = false;
													}
													collisionComponent2->spawnedByArcher = true;
													arrowSpawnedByArcher = collisionComponent2->spawnedByArcher;

												}
												
											}

											//if (entity1->GetID() && entity2->GetID()) 
											//{
											//	PlayerTowerCollision(entity1->GetID(), entity2->GetID());
											//}

											if (behaviourComponent1)
											{
												
												// behaviourComponent1->SetBehaviourState(c_state::Attack);
												collisionComponent1->target = entity2;
												//std::cout << "Circle Collision Detected between Entity" << static_cast<int>(entity1->GetID())
													//<< " and Entity" << static_cast<int>(entity2->GetID()) << std::endl;
											}
										}
									}
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


	void CollisionSystem::EntityToMouseCollision(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities)
	{

		// Get the mouse position from the input system
		VECTORMATH::Vector2D mousePosition = Input::GetMousePosition();

		if (renderImGuiGUI == true) 
		{

			//std::cout << "This is e_editorWidth: " << e_editorWidth << std::endl;
			//std::cout << "This is e_editorHeight: " << e_editorHeight << std::endl;

			float editorWidth = e_editorWidth;
			float editorHeight = e_editorHeight;

			float screenScaleX = 1280.f / editorWidth;
			float screenScaleY = 720.f / editorHeight;

			// Normalize the mouse position
			mousePosition.x = (mousePosition.x - 10.f) * screenScaleX - 1280.f / 2.0f;
			mousePosition.y = 720.f / 2.0f - (mousePosition.y - 20.f) * screenScaleY;
		}

		if (renderImGuiGUI == false) 
		{
			// For non Imgui purposes
			int displayWidth, displayHeight;
			glfwGetFramebufferSize(glfwGetCurrentContext(), &displayWidth, &displayHeight);
			float scaleX = displayWidth / 1280.f;
			float scaleY = displayHeight / 720.f;

			// std::cout << "This is displayWidth: " << displayWidth << std::endl;
			// std::cout << "This is displayHeight: " << displayHeight << std::endl;

			mousePosition.x = ((mousePosition.x) - 1280.f / 2.0f) * scaleX;
			mousePosition.y = (720.f / 2.0f - (mousePosition.y)) * scaleY;
		}

		// Scale factor for the additional scaling in the editor viewport
		//float editorScaleX = static_cast<float>(editorWidth) / 1280.0f;
		//float editorScaleY = static_cast<float>(editorHeight) / 720.0f;

		// Combine scaling factors
		//float scaleX = screenScaleX * editorScaleX;
		//float scaleY = screenScaleY * editorScaleY;

		

		// Iterate through all entities in the editable layer
		for (auto it = entities->begin(); it != entities->end(); ++it)
		{
			Entity* entity = it->second.get();

			// Check if the entity has a CollisionComponent
			if (entity->HasComponent(ComponentType::Collision))
			{
				// Retrieve the CollisionComponent and TransformComponent
				CollisionComponent* collisionComponent = dynamic_cast<CollisionComponent*>(entity->GetComponent(ComponentType::Collision));
				TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(entity->GetComponent(ComponentType::Transform));
				TextureComponent* textureCheck = dynamic_cast<TextureComponent*>(entity->GetComponent(ComponentType::Texture));

				if (collisionComponent->layer == Layer::Editable)
				{
					// Check for point-to-rect collision
					if (CollisionIntersection_PointRect(mousePosition, collisionComponent->aabb))
					{
						// Collision detected, set a flag or perform any actions needed
						collisionComponent->mColliding = true;
						//std::cout << "Mouse collided with Entity " << entity->GetID() << std::endl;
					}
					else
					{
						// No collision, reset the flag or perform cleanup
						collisionComponent->mColliding = false;
					}
				}

				if (collisionComponent->layer == Layer::inGameGUI)
				{
					if (CollisionIntersection_PointRect(mousePosition, collisionComponent->aabb)
						&& Input::IsMouseClicked(LEFT_MOUSE_BUTTON))
					{
						std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl;
						buttonCollision = true;
						lastCollidingEntity = entity->GetID();
						lastCollidingEntityTexture = textureCheck->textureKey.mainIndex;
						isSpawned = true;
						 std::cout << "lastCollidingEntityTexture: " << lastCollidingEntityTexture << std::endl;
						 std::cout << "This is CollisionSystem's buttonCollision: " << buttonCollision << std::endl;
						 std::cout << "Mouse collided with Entity " << entity->GetID() << std::endl;
					}

					// Slotting logic for ingameGUI temporarily until logic system gets put in place
					if (lastCollidingEntityTexture == 10)
					{
						if (textureCheck->textureKey.mainIndex == 10 && textureCheck->textureKey.subIndex == 0)
						{
							textureCheck->textureKey = { 11, 0 };
						}
					}
					if (lastCollidingEntityTexture == 11)
					{
						if (textureCheck->textureKey.mainIndex == 11 && textureCheck->textureKey.subIndex == 0)
						{
							textureCheck->textureKey = { 10, 0 };
						}
					}
				}

				if (collisionComponent->layer == Layer::BeforeSpawn && isSpawned)
				{
					// Check for point-to-rect collision
					if (CollisionIntersection_PointRect(mousePosition, collisionComponent->aabb))
					{
						// Collision detected, set mColliding to true, enable dragging
						collisionComponent->mColliding = true;

						// If released at either starting points
						if ((Input::IsMouseButtonReleased(LEFT_MOUSE_BUTTON) && mousePosition.x >= -640 && mousePosition.x <= -550
							&& mousePosition.y >= -10 && mousePosition.y <= 150)
							|| (Input::IsMouseButtonReleased(LEFT_MOUSE_BUTTON) && mousePosition.x >= 5 && mousePosition.x <= 185
								&& mousePosition.y >= 295 && mousePosition.y <= 360))
						{
							collisionComponent->layer = Layer::World;
							collisionComponent->mColliding = false;
							isStartingPoint = true;
							unitHalfSpawned = false;
							isSpawned = false;
							if (textureCheck->textureKey.mainIndex == 1) 
							{
								infantrySpawned = true;
							}
							if (textureCheck->textureKey.mainIndex == 2)
							{
								tankSpawned = true;
							}
							if (textureCheck->textureKey.mainIndex == 3)
							{
								archerSpawned = true;
							}

							
							ScriptComponent* scriptComponent = dynamic_cast<ScriptComponent*>(entity->GetComponent(ComponentType::Script));
							if (scriptComponent)
							{
								scriptComponent->run = true;
							}
							
							// std::cout << "Layer after release: " << static_cast<int>(collisionComponent->layer) << std::endl;

						}

						// If released elsewhere
						else if (Input::IsMouseButtonReleased(LEFT_MOUSE_BUTTON))
						{
							isStartingPoint = false;
							unitHalfSpawned = true;
							unitID = entity->GetID();
						}
						//std::cout << "Mouse collided with Entity " << entity->GetID();
					}
				

					else
					{
						// No collision, reset the flag or perform cleanup
						collisionComponent->mColliding = false;
					}
				}
				

				if (collisionComponent)
				{


					// Update currentWidth and currentHeight
					if (renderImGuiGUI == false) {
						currentWidth = static_cast<float>(Wwidth);
						currentHeight = static_cast<float>(Wheight);

						// Calculate aspect ratios and update AABB accordingly
						aspectRatioWidth = currentWidth / 1280.f;
						aspectRatioHeight = currentHeight / 720.f;

						// Update AABB min and max values
						float halfWidth_1 = (collisionComponent->c_Width / 2.0f);
						float halfHeight_1 = (collisionComponent->c_Height / 2.0f);

						float minX_1 = (static_cast<float>(transformComponent->position.x) - halfWidth_1) * aspectRatioWidth;
						float maxX_1 = (static_cast<float>(transformComponent->position.x) + halfWidth_1) * aspectRatioWidth;
						float minY_1 = (static_cast<float>(transformComponent->position.y) - halfHeight_1) * aspectRatioHeight;
						float maxY_1 = (static_cast<float>(transformComponent->position.y) + halfHeight_1) * aspectRatioHeight;

						collisionComponent->aabb.min = VECTORMATH::Vec2(minX_1, minY_1);
						collisionComponent->aabb.max = VECTORMATH::Vec2(maxX_1, maxY_1);
					}
					else {
						float halfWidth_1 = (collisionComponent->c_Width / 2.0f);
						float halfHeight_1 = (collisionComponent->c_Height / 2.0f);
						float minX_1 = (static_cast<float>(transformComponent->position.x) - halfWidth_1);
						float maxX_1 = (static_cast<float>(transformComponent->position.x) + halfWidth_1);
						float minY_1 = (static_cast<float>(transformComponent->position.y) - halfHeight_1);
						float maxY_1 = (static_cast<float>(transformComponent->position.y) + halfHeight_1);
						collisionComponent->aabb.min = VECTORMATH::Vec2(minX_1, minY_1);
						collisionComponent->aabb.max = VECTORMATH::Vec2(maxX_1, maxY_1);
					}
				}
			}
		}
	}

}