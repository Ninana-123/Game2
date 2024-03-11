/******************************************************************************/
/*!
\file		StatsComponent.h
\author		Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807

\par		a.junshengaloysius@digipen.edu

\date		23/01/2024

\brief		Contains the stats components of a given entity.
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#pragma once
#include "Component.h"
#include "EntityStats.h"

namespace Engine
{
	class StatsComponent : public Component
	{
	public:
		unit_type type = unit_type::none;
		float health = 0.0f;
		float range = 0.0f;
		bool statsInitialized = false;

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
			cloneComponent->range = range;
			//cloneComponent->statsInitialized = statsInitialized;

			return cloneComponent;
		}

		void Serialize(std::ostream& outputStream) const override {
			outputStream << "Health: " << health << '\n';
			outputStream << "Range: " << range << '\n';
			//outputStream << "StatsInitialized: " << statsInitialized << '\n';
		}

		void Deserialize(std::istream& inputStream) override {
			std::string temp;
			//int buffer{};
			inputStream >> temp >> health;
			inputStream >> temp >> range;
		}
	};
}