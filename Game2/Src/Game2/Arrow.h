#pragma once

#ifndef ARROW_H
#define ARROW_H

#include "pch.h"
#include "Vector2d.h"
#include "Entity.h"
#include "TransformComponent.h"

#define ARROW_COUNT 100
#define ARROW_HEIGHT 20
#define ARROW_WIDTH 20

namespace Engine {

	class Arrow {
	public:
		TransformComponent transform;
		bool enabled = false;
		VECTORMATH::Vector2D direction;
		float timeSinceLastDmgDeal = 0;
	};

	struct ArrowPool {
		Arrow arrow[ARROW_COUNT]{};
		Arrow* activeArrow[ARROW_COUNT]{};
		int activeSize = 0;
	};

	void Add_Arrow(ArrowPool& pool, VECTORMATH::Vector2D archPos, VECTORMATH::Vector2D playerPos);

	void Init_ArrowPool(ArrowPool& pool);

	void Draw_Arrow(ArrowPool& pool);

	void AI_Arrow(ArrowPool& arrow);

	void Remove_Arrow(int index, ArrowPool& arrow);

	void Free_Arrow();

}

#endif

