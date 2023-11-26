/******************************************************************************/
/*!
\file		Component.h
\author 	Tristan Tham Rui Hong
\par    	email: t.tham@digipen.edu
\date   	29/09/2923
\brief		Declaration of the Component class.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#pragma once
#include "EngineTypes.h"

namespace Engine
{
    class Component
    {
    public:
        /**
         * @brief Virtual destructor for the Component class.
         */
        virtual ~Component() = default;

        /**
         * @brief Gets the type of the component.
         *
         * @return The type of the component as ComponentType.
         */
        virtual ComponentType GetType() const = 0;

        /**
         * @brief Creates a clone of the component.
         *
         * @return A new Component pointer that is a clone of the current component.
         */
        virtual Component* Clone() const = 0;

        /**
         * @brief Serializes the component to an output stream.
         *
         * @param os The output stream to serialize the component to.
         */
        virtual void Serialize(std::ostream& os) const = 0;

        /**
         * @brief Deserializes the component from an input stream.
         *
         * @param is The input stream to deserialize the component from.
         */
        virtual void Deserialize(std::istream& is) = 0;
    };
}