/******************************************************************************/
/*!
\file		BasicShader
\author 	DigiPen
\par    	email: k.junlinwayne@digipen.edu
\date   	August 29, 2023
\brief		This file contains 

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#shader vertex
#version 450 core

layoyt(location = 0) in vec4 position

void main()
{
gl_position = position;
};

#shader fragment
#version 450 core

layoyt(location = 0) out vec4 color

void main()
{
color = vec4(1.0, 0.0, 0.0, 1.0);
};