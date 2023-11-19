#pragma once

#include "Component.h"
#include "inGameGUISystem.h"
#include "EngineTypes.h"

namespace Engine
{
	class inGameGUIComponent : public Component
	{
	public:

		//int meow = 0;
		ComponentType GetType() const override { return ComponentType::inGameGUI; }

		Component* Clone() const override
		{
			inGameGUIComponent* cloneComponent = new inGameGUIComponent();

			return cloneComponent;
		}

		void Serialize(std::ostream& outputStream) const override {
			//outputStream << "Meow: " << meow << '\n';
		}

		void Deserialize(std::istream& inputStream) override {
			std::string temp;
			//inputStream >> temp >> meow;
		}

	};
}