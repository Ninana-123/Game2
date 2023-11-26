/******************************************************************************/
/*!
\file		font.cpp
\author 	Teo Sheen Yeoh
\par    	email: t.sheenyeoh@digipen.edu
\date   	August 29, 2023
\brief		 This file defines the member functions of the Camera class, 
            which is responsible for managing the camera's view and projection matrices 
            in the game engine. It includes functions to set up the orthographic projection matrix,
            recalculate the view matrix based on the camera's position and rotation, 
            and update the camera's position using input controls.

			Copyright (C) 2023 DigiPen Institute of Technology.
			Reproduction or disclosure of this file or its contents without the prior
			written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/


#pragma once
#include "pch.h"
#include <glm/glm.hpp>
#include "Input.h"

namespace Engine
{
	class Camera
	{
	public:

		Camera(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition()
		{
			return m_Position;
		}

		void SetPosition(const glm::vec3& position) 
		{
			m_Position = position;
		}

		void SetRotation(float rotation)
		{
			m_Rotation = rotation;
		}

		void Translate(const glm::vec3& translation)
		{
			m_Position += translation;
			RecalculateViewMatrix();
		}

		void RecalculateProjectionMatrix(int width, int height);

		const glm::mat4& GetProjectionMatrix()const 
		{
			return m_ProjectionMatrix; 
		}
		const glm::mat4& GetViewMatrix()const 
		{
			return m_ViewMatrix; 
		}
		const glm::mat4& GetViewProjectionMatrix()const 
		{ 
			return m_ViewProjectionMatrix; 
		}

		virtual void UpdatePosition(const Input& input, float CameraSpeed);
		//void HandleMouseScroll(float yOffset);

	protected:

		void RecalculateViewMatrix();
		float m_Rotation = 0.0f;
		float m_Left;
		float m_Right;
		float m_Bottom;
		float m_Top;
		float m_Zoom;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
	};

	
}