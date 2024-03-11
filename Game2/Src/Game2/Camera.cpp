/******************************************************************************/
/*!
\file		Camera.cpp
\author 	Teo Sheen Yeoh
\par    	email: t.sheenyeoh@digipen.edu
\date   	August 29, 2023
\brief       This file defines the member functions of the Camera class, 
            which is responsible for managing the camera's view and projection matrices 
            in the game engine. It includes functions to set up the orthographic projection matrix,
            recalculate the view matrix based on the camera's position and rotation, 
            and update the camera's position using input controls.
          

            Copyright (C) 2023 DigiPen Institute of Technology.
            Reproduction or disclosure of this file or its contents without the prior
            written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "pch.h"
#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Engine
{

    Camera::Camera(float left, float right, float bottom, float top)
        : m_Left(left), m_Right(right), m_Bottom(bottom), m_Top(top),
        m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
        m_ViewMatrix(1.0f), m_Zoom(1.0f)
    {
        // vertex pos * world matrix(world) * view matrix * projection matrix
        // camera  =  view * projection
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void Camera::RecalculateViewMatrix()
    {
        // Recalculate the view matrix based on the camera's position and rotation
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
            glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0, 0, 1));

        // Update the view matrix and view-projection matrix
        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    //void Camera::HandleMouseScroll(float yOffset)
    //{
    //    m_Zoom += yOffset * 0.1f; // Adjust the zoom factor based on the mouse scroll input
    //    m_Zoom = glm::clamp(m_Zoom, 0.1f, 10.0f);

    //    // Update the projection matrix based on the new zoom factor
    //    m_ProjectionMatrix = glm::ortho(
    //        m_Zoom * m_Left, m_Zoom * m_Right,
    //        m_Zoom * m_Bottom, m_Zoom * m_Top, -1.0f, 1.0f);

    //    RecalculateViewMatrix();
    //}

    void Camera::UpdatePosition(const Input& input, float CameraSpeed)
    {
        // Update the camera's position based on input controls
        glm::vec3 translation(0.0f);

        bool CameraLeft = input.IsKeyPressed(KEY_J);
        bool CameraRight = input.IsKeyPressed(KEY_L);
        bool CameraUp = input.IsKeyPressed(KEY_I);
        bool CameraDown = input.IsKeyPressed(KEY_K);

        if (CameraLeft)
        {
            translation.x -= CameraSpeed;
        }
        if (CameraRight)
        {
            translation.x += CameraSpeed;
        }
        if (CameraUp)
        {
            translation.y += CameraSpeed;
        }
        if (CameraDown)
        {
            translation.y -= CameraSpeed;
        }

        if (translation != glm::vec3(0.0f))
        {
            Translate(translation);
        }
    }
}