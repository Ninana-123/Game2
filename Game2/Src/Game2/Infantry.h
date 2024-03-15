/******************************************************************************/
/*!
\file		Infantry.h
\author 	Tristan Tham Rui Hong
\par    	email: t.tham@digipen.edu
\date   	01/03/2924
\brief		Declaration of the ScriptSystem class

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#pragma once
#include "ScriptSystem.h"

namespace Engine
{
	class Infantry : public Script
	{
	public:
		void Initialize();

		void Update() override;

	private:
		float ms;
		float hp;
	};
}