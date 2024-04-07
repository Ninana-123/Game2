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
	class ScriptFactory;

	extern ScriptFactory* g_ScriptFactory;

	class Script //Base class
	{
	public:

		virtual void Update() = 0;

		virtual ~Script() = default;

	};

	class ScriptComponent : public Component
	{
	public:
		bool run = false;
		bool alive = true;
		Script* script = nullptr;
		EntityID entity = EMPTY_ID;
		ScriptType currentScriptType = ScriptType::Empty;

		void InitializeScript();

		void SetScriptType(ScriptType type);
		
		void SetEntity(EntityID entity_);

		std::string ScriptToString(ScriptType type);

		Script* GetScript() const;
	
		/*!*****************************************************************

		\brief
		Getter for this Components enum

		\return  ComponentType
		Returns an enum of the component Type

		********************************************************************/

		ComponentType GetType() const override;

		/*!*****************************************************************

		\brief
		Cloner for this component

		\return  Component*
		Clone component with cloned data members

		********************************************************************/
		Component* Clone() const override;
	

		void Serialize(std::ostream& outputStream) const override;

		void Deserialize(std::istream& inputStream) override;

	};
}
#endif ENGINE_SCRIPTCOMPONENT_H