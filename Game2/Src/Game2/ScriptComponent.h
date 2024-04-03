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

		virtual void Update() = 0;


		virtual ~Script() = default;

	};

	class ScriptComponent : public Component
	{
	public:

		//ScriptFactory* scriptFactory = nullptr; // Pointer to ScriptFactory
		std::unique_ptr<Script> script = nullptr;
		Entity* entity = nullptr;

		void SetScriptType(ScriptType type)
		{
			UNREFERENCED_PARAMETER(type);
			// Make switch, create new script object not link pointer
			//script = scriptFactory->AddScript(type, entity);
		}
		
		void SetEntity(Entity* entity_) { this->entity = entity_; }

		Script* GetScript() const
		{
			return script.get();
		}

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