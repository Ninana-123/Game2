#pragma once
#include "Component.h"
#include "EntityStats.h"

namespace Engine
{
	class StatsComponent : public Component
	{
	public:
		float health = 0.0f;

		/*!*****************************************************************

		\brief
		Getter for this Components enum

		\return  ComponentType
		Returns an enum of the component Type

		********************************************************************/

		ComponentType GetType() const override { return ComponentType::Stats; }

		/*!*****************************************************************

		\brief
		Cloner for this component

		\return  Component*
		Clone component with cloned data members

		********************************************************************/
		Component* Clone() const override
		{
			StatsComponent* cloneComponent = new StatsComponent();
			cloneComponent->health = health;

			return cloneComponent;
		}

		void Serialize(std::ostream& outputStream) const override {
			outputStream << "Health: " << health << '\n';
		}

		void Deserialize(std::istream& inputStream) override {
			std::string temp;
			int buffer;
			inputStream >> temp >> health;

		}
	};
}