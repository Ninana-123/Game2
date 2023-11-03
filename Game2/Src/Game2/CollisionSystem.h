/******************************************************************************/
/*!
\file		CollisionSystem.h
\author		Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807
 co			Tristan Tham Rui Hong,  t.tham,				2200794

\par		a.junshengaloysius@digipen.edu
\date		10/09/2023
\brief		Contains the declaration for the logic of AABB, Circle to Circle and Circle to AABB Collision

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#pragma once

#include "System.h"
#include "Vector2d.h"


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
	class CollisionSystem : public System //CollisionSystem class, Child class of System base class
	{
	public:
		/*!*****************************************************************

		 \brief
			Logic of systems calculating logic on component data from each entity

		\param[in] entities
			map container of entities with references

		********************************************************************/
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

		// Define a struct to represent an edge of a polygon
		struct Edge {
			VECTORMATH::Vec2 normal;
			float min, max;
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


		/*!*****************************************************************

		 \brief
			The logic of point and AABB collision.

		\param[in] point
			Point coordinate.

		\param[in] aabb
			The bound of the rectangle.

		\return  boolean
			Returns true if there is a collision, false is there is not.

		********************************************************************/
		bool CollisionIntersection_PointRect(const VECTORMATH::Vec2& point, const AABB& aabb);

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

		/**************************************************************************/
		/*!
		\brief Check if a specific area defined by its center, width, and height has been clicked.

		\param[in] area_center_x
		The x-coordinate of the center of the area.

		\param[in] area_center_y
		The y-coordinate of the center of the area.

		\param[in] area_width
		The width of the area.

		\param[in] area_height
		The height of the area.

		\param[in] click_x
		The x-coordinate of the click.

		\param[in] click_y
		The y-coordinate of the click.

		\return
		`true` if the area has been clicked; otherwise, `false`.

		*/
		/**************************************************************************/
		bool IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);

		/**************************************************************************/
		/*!
		\brief Project a polygon onto an axis and determine the minimum and maximum values of the projection.

		\param[in] polygon
		A vector containing 2D vertices of the polygon to be projected.

		\param[in] axis
		The axis onto which the polygon is projected.

		\param[out] min
		The minimum value of the projection.

		\param[out] max
		The maximum value of the projection.

		*/
		/**************************************************************************/
		void ProjectPolygon(const std::vector<VECTORMATH::Vec2>& polygon, const VECTORMATH::Vec2& axis, float& min, float& max);

		/**************************************************************************/
		/*!
		\brief Determine if two polygons intersect using the Separating Axis Theorem (SAT) method.

		\param[in] polygon1
		A vector containing 2D vertices of the first polygon.

		\param[in] polygon2
		A vector containing 2D vertices of the second polygon.

		\param[in] rotationAngle1
		The rotation angle of the first polygon.

		\param[in] rotationAngle2
		The rotation angle of the second polygon.

		\return
		`true` if the polygons intersect; otherwise, `false`.

		*/
		/**************************************************************************/
		bool PolygonIntersectionSAT(const std::vector<VECTORMATH::Vec2>& polygon1, const std::vector<VECTORMATH::Vec2>& polygon2,
			float rotationAngle1, float rotationAngle2);

		/**************************************************************************/
		/*!
		\brief Rotate a polygon by a specified angle around a given center point.

		\param[in] polygon
		A vector containing 2D vertices of the polygon to be rotated.

		\param[in] angle
		The angle by which the polygon is to be rotated.

		\param[in] center
		The center point for the rotation.

		*/
		/**************************************************************************/
		void RotatePolygon(std::vector<VECTORMATH::Vec2>& polygon, float angle, VECTORMATH::Vec2 center);

		/**************************************************************************/
		/*!
		\brief Check for collisions between entities in a collection and update their states as needed.

		\param[in] entities
		A pointer to an `std::unordered_map` containing entities associated with unique IDs.

		*/
		/**************************************************************************/
		void EntityToEntityCollision(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities);
	};
}