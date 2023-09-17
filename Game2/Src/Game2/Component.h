#pragma once
#include "EngineTypes.h"

namespace Engine
{
	class Component 
	{
	public:
		virtual ComponentType GetType() const = 0;
		virtual Component* Clone() const = 0;
	};
}