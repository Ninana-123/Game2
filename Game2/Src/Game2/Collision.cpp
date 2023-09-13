#include "pch.h"
#include "Collision.h"

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
bool CollisionIntersection_RectRect(const AABB& aabb1, const glm::vec2& vel1,
	const AABB& aabb2, const glm::vec2& vel2)
{
	UNREFERENCED_PARAMETER(aabb1);
	UNREFERENCED_PARAMETER(vel1);
	UNREFERENCED_PARAMETER(aabb2);
	UNREFERENCED_PARAMETER(vel2);

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

	glm::vec2 relVelocity = { 0, 0 }; 
	glm::vec2 tFirst = { 0, 0 };
	glm::vec2 tLast = { g_dt, g_dt };
	glm::vec2 tTemp = { 0, 0 };
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

