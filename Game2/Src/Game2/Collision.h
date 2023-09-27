#pragma once
/******************************************************************************/
/*!
\file		Collision.h
\author		Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807
\par		a.junshengaloysius@digipen.edu
\date		01/03/2023
\brief		Contains the declaration for the logic of AABB Collision

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

#ifndef CSD1130_COLLISION_H_
#define CSD1130_COLLISION_H_

/**************************************************************************/
/*!

	*/
	/**************************************************************************/

#pragma once

#include "Vector2d.h"

struct AABB
{
	VECTORMATH::Vec2 min;
	VECTORMATH::Vec2 max;
};

struct Circle {
	VECTORMATH::Vec2 center;
	float radius;
};


bool CollisionIntersection_CircleCircle(const Circle& circle1, const VECTORMATH::Vec2& vel1,
	const Circle& circle2, const VECTORMATH::Vec2& vel2);

bool CollisionIntersection_RectRect(const AABB& aabb1, const VECTORMATH::Vec2& vel1,
	const AABB& aabb2, const VECTORMATH::Vec2& vel2);

bool CollisionIntersection_CircleRect(const Circle& circle, const AABB& rect);



#endif // CSD1130_COLLISION_H_