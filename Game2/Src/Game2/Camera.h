/******************************************************************************/
/*!
\file		Camera.h
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

		/**
		 * @brief Constructs a Camera object with the specified orthographic projection parameters.
		 *
		 * @param left The left coordinate of the projection volume.
		 * @param right The right coordinate of the projection volume.
		 * @param bottom The bottom coordinate of the projection volume.
		 * @param top The top coordinate of the projection volume.
		 */
		Camera(float left, float right, float bottom, float top);

		/**
		* @brief Gets the current position of the camera.
		*
		* @return A constant reference to a glm::vec3 representing the position of the camera.
		*/
		const glm::vec3& GetPosition()
		{
			return m_Position;
		}

		/**
		* @brief Sets the position of the camera.
		*
		* @param position A constant reference to a glm::vec3 representing the new position of the camera.
		*/
		void SetPosition(const glm::vec3& position)
		{
			m_Position = position;
		}

		/**
		* @brief Sets the rotation of the camera.
		*
		* @param rotation A float representing the new rotation angle of the camera.
		*/
		void SetRotation(float rotation)
		{
			m_Rotation = rotation;
		}

		/**
		* @brief Translates the camera by the given translation vector.
		*
		* @param translation A constant reference to a glm::vec3 representing the translation to apply.
		*/
		void Translate(const glm::vec3& translation)
		{
			m_Position += translation;
			RecalculateViewMatrix();
		}

		/**
		* @brief Gets the orthographic projection matrix of the camera.
		*
		* @return A constant reference to a glm::mat4 representing the orthographic projection matrix.
		*/
		const glm::mat4& GetProjectionMatrix()const
		{
			return m_ProjectionMatrix;
		}

		/**
		* @brief Gets the view matrix of the camera.
		*
		* @return A constant reference to a glm::mat4 representing the view matrix.
		*/
		const glm::mat4& GetViewMatrix()const
		{
			return m_ViewMatrix;
		}

		/**
		* @brief Gets the view-projection matrix of the camera.
		*
		* @return A constant reference to a glm::mat4 representing the view-projection matrix.
		*/
		const glm::mat4& GetViewProjectionMatrix()const
		{
			return m_ViewProjectionMatrix;
		}

		/**
		* @brief Updates the camera's position based on input controls.
		*
		* @param input Reference to the Input object for processing user input.
		* @param CameraSpeed The movement speed of the camera.
		*/
		virtual void UpdatePosition(const Input& input, float CameraSpeed);
		//void HandleMouseScroll(float yOffset);

	protected:

		/**
		* @brief Recalculates the view matrix based on the camera's position and rotation.
		*/
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