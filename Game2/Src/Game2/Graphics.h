/******************************************************************************/
/*!
\file		Graphics.h
\authors 	Tristan Tham Rui Hong
			Wayne Kwok Jun Lin

\par    	email: k.junlinwayne@digipen.edu
				   t.tham@digipen.edu

\date   	August 29, 2023
\brief		This file contains the interface for the graphics component

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once
#include "Game2/System.h"

namespace Engine
{

	class Graphics : public ISystem
	{
	public:
		Graphics();
		~Graphics();
		
	private:
		//add all the graphics library functions here
		void Initialize();
		void Update();
	    //void SetVertex(float x1, float y1, float x2, float y2, float x3, float y3);
		//void CreateWindow(width, height...) clash with windows system xujie is making.
		//void CreateBuffer(...)
		//void Draw();
	public:
		int ScreenWidth{};
		int SceenHeight{};
	};

}