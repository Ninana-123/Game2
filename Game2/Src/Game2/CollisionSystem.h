#pragma once
/******************************************************************************/
/*!
\file		Collision.h
\author		Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807
 co			Tristan Tham Rui Hong,  t.tham,				2200794

\par		a.junshengaloysius@digipen.edu
\date		01/03/2023
\brief		Contains the declaration for the logic of AABB Collision

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/
#include "System.h"
#include "Vector2d.h"
#include "EngineTypes.h"


#ifndef CSD1130_COLLISION_H_
#define CSD1130_COLLISION_H_

/**************************************************************************/
/*!

*/
/**************************************************************************/

#pragma once

#endif // CSD1130_COLLISION_H_

namespace Engine
{
	class CollisionSystem : public System
	{
	public:

		void Update (std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) override;

		struct AABB
		{
			VECTORMATH::Vec2 min;
			VECTORMATH::Vec2 max;
		};

		struct Circle 
		{
			VECTORMATH::Vec2 center;
			float radius;
		};

		bool CollisionIntersection_RectRect(const AABB& aabb1, const VECTORMATH::Vec2& vel1,
			const AABB& aabb2, const VECTORMATH::Vec2& vel2);

		bool CollisionIntersection_CircleCircle(const Circle& circle1, const VECTORMATH::Vec2& vel1,
			const Circle& circle2, const VECTORMATH::Vec2& vel2);

		bool CollisionIntersection_CircleRect(const Circle& circle, const AABB& rect);

	};
}