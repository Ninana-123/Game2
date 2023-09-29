/******************************************************************************/
/*!
\file		Component.h
\author 	Tristan Tham Rui Hong
\par    	email: l.xujie@digipen.edu
\date   	29/09/2923
\brief		Declaration of the Component class.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once
#include "EngineTypes.h"

namespace Engine
{
	class Component 
	{
	public:
		virtual ~Component() = default;
		virtual ComponentType GetType() const = 0;
		virtual Component* Clone() const = 0;
	};
}