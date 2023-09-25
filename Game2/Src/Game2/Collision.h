/******************************************************************************/
/*!
\file		Collision.h
\author		Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807
\par		a.junshengaloysius@digipen.edu
\date		10/09/2023
\brief		Contains the declaration for the logic of AABB Collision

 */
 /******************************************************************************/

#pragma once

#include "mathLib.h"

struct AABB
{
	VECTORMATH::Vec2 min;
	VECTORMATH::Vec2 max;
};

bool CollisionIntersection_RectRect(const AABB& aabb1, const VECTORMATH::Vec2& vel1,
	const AABB& aabb2, const VECTORMATH::Vec2& vel2);
