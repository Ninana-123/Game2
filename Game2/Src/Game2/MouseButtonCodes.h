/******************************************************************************/
/*!
\file		MouseButtonCodes.h
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	29/09/2923
\brief		Defines mouse button codes and a mapping of mouse button codes 
            to mouse button names.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#ifndef ENGINE_MOUSEBUTTON_H
#define ENGINE_MOUSEBUTTON_H

#include <map>

#define LEFT_MOUSE_BUTTON         0
#define RIGHT_MOUSEBUTTON         1
#define MOUSE_BUTTON_3         2
#define MOUSE_BUTTON_4         3
#define MOUSE_BUTTON_5         4
#define MOUSE_BUTTON_6         5
#define MOUSE_BUTTON_7         6
#define MOUSE_BUTTON_8         7


namespace Engine {
    using MouseCode = unsigned int;

    namespace Mouse {

        // Mapping of mouse button codes to mouse button names
        const std::map<MouseCode, std::string> mouseMap = {
            {0, "Left Mouse Button"},
            {1, "Right Mouse Button"},
            {2, "Button2"},
            {3, "Button3"},
            {4, "Button4"},
            {5, "Button5"},
            {6, "Button6"},
            {7, "Button7"}
        };
    }
}
#endif ENGINE_MOUSEBUTTON_H