#include "pch.h"
#include "Arrow.h"
#include "WindowsWindow.h"

namespace Engine {

#define ARROW_HALF_X glfwGetFramebufferSize(window, NULL) / 2.0f
#define ARROW_HALF_Y glfwGetFramebufferSize(window, NULL) / 2.0f

#define ARROW_BOUNDARY_X (ARROW_HALF_X + 100)
#define ARROW_BOUNDARY_Y (ARROW_HALF_Y + 100)

#define ARROW_SPEED 200.f

	void Remove_Arrow(int index, ArrowPool& pool) {
		pool.activeArrow[index]->enabled = false;
		if (index < (pool.activeSize - 1)) {
			Arrow* temp = pool.activeArrow[index];
			pool.activeArrow[index] = pool.activeArrow[pool.activeSize - 1];
			pool.activeArrow[pool.activeSize - 1] = temp;
		}
		pool.activeSize -= 1;
	}

	void Add_Arrow(ArrowPool& pool, VECTORMATH::Vector2D archPos, VECTORMATH::Vector2D playerPos) {
		for (int i = 0; i < ARROW_COUNT; i++) {
			if (pool.activeArrow[i]->enabled == false) {
				pool.activeArrow[i]->enabled = true;
				pool.activeArrow[i]->transform.position = archPos;
				pool.activeArrow[i]->transform.scaleX = 2;
				pool.activeArrow[i]->transform.scaleY = 2;
				pool.activeArrow[i]->transform.rot = std::atan2(playerPos.y - archPos.y, playerPos.x - archPos.x);
				VECTORMATH::Vector2D direction1;
				VECTORMATH::Vector2D temp = playerPos - archPos;
				Vector2DNormalize(direction1, temp);
				pool.activeArrow[i]->direction = direction1;
				pool.activeSize += 1;
				break;
			}
		}
	}

	void Init_ArrowPool(ArrowPool& pool) {
		pool.activeSize = 0;

	}

}