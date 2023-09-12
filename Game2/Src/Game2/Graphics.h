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
		int ScreenWidth;
		int SceenHeight;
	};

}