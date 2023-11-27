/******************************************************************************/
/*!
\file		BehaviourComponent.h
\author		Liu Xujie
\par		l.xujie@digipen.edu
\date		19/11/23
\brief		Contains the interface of the Behaviour Component

 */
 /******************************************************************************/

#pragma once
#include "Component.h"
#include "EngineTypes.h"
#include "Vector2d.h"
#include <fstream>

namespace Engine
{

	class BehaviourComponent : public Component
	{
	protected:
		unsigned int m_behaviourIndex = 0;
	public:
		
		inline void SetBehaviourIndex(const unsigned int& behaviourIndex) {
			m_behaviourIndex = behaviourIndex;
		}
		inline unsigned int& GetBehaviourIndex() noexcept {
			return m_behaviourIndex;
		}


		/*!*****************************************************************

		\brief
		Getter for this Components enum

		\return  ComponentType
		Returns an enum of the component Type

		********************************************************************/

		ComponentType GetType() const override { return ComponentType::Logic; }

		/*!*****************************************************************
		\brief
		Cloner for this component

		\return  Component*
		Clone component with cloned data members

		********************************************************************/
		Component* Clone() const override
		{
			BehaviourComponent* cloneComponent = new BehaviourComponent();
			cloneComponent->m_behaviourIndex = m_behaviourIndex;
			return cloneComponent;
		}

		void Serialize(std::ostream& outputStream) const override {
			outputStream << "BehaviourIndex: " << m_behaviourIndex << std::endl;
		}

		void Deserialize(std::istream& inputStream) override {
			std::string temp;
			//int buffer;
			inputStream >> temp >> m_behaviourIndex;
		}
	};
}