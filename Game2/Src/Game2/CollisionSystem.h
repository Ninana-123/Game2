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
		bool CollisionIntersection_RectRect(const AABB& aabb1, const VECTORMATH::Vec2& vel1,
			const AABB& aabb2, const VECTORMATH::Vec2& vel2);

		/**************************************************************************/
		/*!
		\brief Determines if there is an intersection between two moving circles.

		\param[in] circle1
			The first Circle object representing the first moving circle.

		\param[in] vel1
			The velocity vector of the first circle.

		\param[in] circle2
			The second Circle object representing the second moving circle.

		\param[in] vel2
			The velocity vector of the second circle.

		\return
			True if the two moving circles intersect during their motion, false otherwise.

		*/
		/**************************************************************************/
		bool CollisionIntersection_CircleCircle(const Circle& circle1, const VECTORMATH::Vec2& vel1,
			const Circle& circle2, const VECTORMATH::Vec2& vel2);

		/**************************************************************************/
		/*!
		\brief Determines if there is an intersection between a circle and an axis-aligned bounding box (AABB).

		\param[in] circle
			The Circle object representing the circle.

		\param[in] rect
			The AABB object representing the axis-aligned bounding box.

		\return
			True if the circle intersects with the AABB, false otherwise.

		*/
		/**************************************************************************/
		bool CollisionIntersection_CircleRect(const Circle& circle, const AABB& rect);

	};
}