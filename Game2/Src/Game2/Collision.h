#pragma once

#include <glm/vec2.hpp> // glm::vec2
#include <glm/vec3.hpp> // glm::vec3
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

struct AABB
{
	glm::vec2	min;
	glm::vec2	max;
};

bool CollisionIntersection_RectRect(const AABB& aabb1, const glm::vec2& vel1,
	const AABB& aabb2, const glm::vec2& vel2);
