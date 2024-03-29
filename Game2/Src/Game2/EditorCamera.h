/******************************************************************************/
/*!
\file		EditorCamera.h
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	01/11/2023
\brief		This file contains the implementation of the Asset Manager which
			handles the assets used by the engine.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#ifndef ENGINE_EDITORCAMERA_H
#define ENGINE_EDITORCAMERA_H

#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Input.h"
#include "Logger.h"
#include "Application.h"
namespace Engine
{
	class EditorCamera : public Camera
	{
	public:
		/*!**********************************************************************
		\brief
		Constructor for the EditorCamera class.

		\param left
		The left boundary of the orthographic projection.

		\param right
		The right boundary of the orthographic projection.

		\param bottom
		The bottom boundary of the orthographic projection.

		\param top
		The top boundary of the orthographic projection.
		*************************************************************************/
		EditorCamera(float left, float right, float bottom, float top)
			: Camera(left, right, bottom, top)
		{
			// You can initialize any additional parameters specific to the EditorCamera here.
		}

		/*
		void Zoom(float delta)
		{
			m_Zoom += delta;
			m_Zoom = glm::clamp(m_Zoom, 0.1f, 10.0f);  // Limit the zoom to prevent too much zoom-in or zoom-out.

			// Update the projection matrix based on the new zoom factor.
			m_ProjectionMatrix = glm::ortho(
				m_Zoom * m_Left, m_Zoom * m_Right,
				m_Zoom * m_Bottom, m_Zoom * m_Top, -1.0f, 1.0f);

			RecalculateViewMatrix();
		}
		*/

		/*!*********************************************************************
		\brief
		Applies a rotation to the camera's current orientation.

		\param delta
		The amount by which to change the camera's rotation.
		*************************************************************************/
		void Rotate(float delta)
		{
			m_Rotation += delta;

			while (m_Rotation >= 360.0f) m_Rotation -= 360.0f;
			while (m_Rotation < 0.0f) m_Rotation += 360.0f;

			RecalculateViewMatrix();
		}

		/*!*********************************************************************
		\brief
		Moves the camera's position based on a 2D translation vector.

		\param translation
		The glm::vec2 translation vector indicating how far to move the camera along the x and y axes.
		*************************************************************************/
		void Pan(const glm::vec2& translation)
		{
			m_Position.x += translation.x;
			m_Position.y += translation.y;
			RecalculateViewMatrix();
		}

		/*!*********************************************************************
		\brief
		Resets the camera's projection and view matrices to default values.

		\param left
		The left boundary of the orthographic projection.

		\param right
		The right boundary of the orthographic projection.

		\param bottom
		The bottom boundary of the orthographic projection.

		\param top
		The top boundary of the orthographic projection.
		*************************************************************************/
		void ResetCameraPos(float left, float right, float bottom, float top) {
			m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
			m_ViewMatrix = glm::mat4(1.0f);
			m_Zoom = 1.0f;
			m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;
			// Reset the camera position to the origin
			m_Position = glm::vec3(0.0f, 0.0f, 0.0f);

			m_Rotation = 0.0f; // Assuming a scalar for 2D rotation around Z-axis

			// Recalculate the view matrix with the new position and rotation
			RecalculateViewMatrix();
		}

		/*!*********************************************************************
		\brief
		Updates the camera's position based on user input and specific editor controls.

		\param input
		The Input object containing the current state of user inputs.

		\param CameraSpeed
		The speed at which the camera should move or zoom.
		**************************************************************************/
		void UpdatePosition(const Input& input, float CameraSpeed) override
		{
			// Default camera position update functionality.
			Camera::UpdatePosition(input, CameraSpeed);

			// Editor-specific behaviors:

			// Pan camera using arrow keys.
			if (input.IsKeyPressed(KEY_L)) {
				Pan(glm::vec2(CameraSpeed, 0));
				Logger::GetInstance().Log(LogLevel::Debug, "Currently moving cam right");
				
			}
			if (input.IsKeyPressed(KEY_J)) {
				Pan(glm::vec2(-CameraSpeed, 0));
			}
			if (input.IsKeyPressed(KEY_I)) {
				Pan(glm::vec2(0, CameraSpeed));
			}
			if (input.IsKeyPressed(KEY_K)) {
				Pan(glm::vec2(0, -CameraSpeed));
			}

			if (input.IsKeyTriggered(KEY_SPACE)) {
				ResetCameraPos(-640.0f, 640.0f, -360.0f, 360.0f);
			}


			//// Rotate camera continuously while 'U' key is held down.
			//if (input.IsKeyPressed(KEY_U)) {
			//	//float deltaTime = (float)dt;  // Assuming your Input class has a method to get the time since the last frame.
			//	float rotationAngle = m_RotationSpeed * static_cast<float>(fixedDeltaTime);
			//	Rotate(rotationAngle);
			//}
			// Rotate camera continuously while 'U' key is held down.
			if (input.IsKeyPressed(KEY_U)) {
				float rotationAngle = m_RotationSpeed * static_cast<float>(fixedDeltaTime);
				Rotate(rotationAngle);
			}

			/*
			if (input.IsKeyPressed(KEY_Y)) {
				Zoom(CameraSpeed);  // Positive delta for zooming in.
			}

			if (input.IsKeyPressed(KEY_H)) {
				Zoom(-CameraSpeed);  // Negative delta for zooming out.
			}
			*/
		}


		// If there are other editor-specific functions, implement them here.

	protected:


	private:
		// Add any additional member variables specific to the EditorCamera.
		const float m_RotationSpeed = 3.0f;  // Degrees per second
	};
}
#endif ENGINE_EDITORCAMERA_H