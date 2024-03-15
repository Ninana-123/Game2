/******************************************************************************/
/*!
\file		ScriptComponent.h
\author 	Tristan Tham Rui Hong
\par    	email: t.tham@digipen.edu
\date   	01/03/2924
\brief		Declaration of the ScriptComponent class

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once

#ifndef ENGINE_SCRIPTCOMPONENT_H
#define ENGINE_SCRIPTCOMPONENT_H


namespace Engine
{
	class Script //Base class
	{
	public:
		virtual void Initialize() {}

		virtual void Update() {}

		virtual void Cleanup() {}

	};

	class ScriptComponent : public Component
	{
	public:

		ScriptComponent() {};

		void SetScript(Script* newScript) 
		{
			script = newScript;
		}

		Script* GetScript() const 
		{
			return script;
		}

	private:
		Script* script = nullptr;

	public:
		/*!*****************************************************************

		\brief
		Getter for this Components enum

		\return  ComponentType
		Returns an enum of the component Type

		********************************************************************/

		ComponentType GetType() const override { return ComponentType::Script; }

		/*!*****************************************************************

		\brief
		Cloner for this component

		\return  Component*
		Clone component with cloned data members

		********************************************************************/
		Component* Clone() const override
		{
			ScriptComponent* cloneComponent = new ScriptComponent();
			//cloneComponent->statsInitialized = statsInitialized;

			return cloneComponent;
		}

		void Serialize(std::ostream& outputStream) const override 
		{
			UNREFERENCED_PARAMETER(outputStream);
		}

		void Deserialize(std::istream& inputStream) override 
		{
			UNREFERENCED_PARAMETER(inputStream);
		}
	};
}
#endif ENGINE_SCRIPTCOMPONENT_H