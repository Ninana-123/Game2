#pragma once


namespace Engine
{
	class Entity;
	class System;

	class TestSystem : public System
	{
	public:
		TestSystem() {};
		~TestSystem() {};

		void Update(Entity& entity) override;
	};
}