/******************************************************************************/
/*!
\file		Matrix3x3Lib.cpp
\author		Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807
\par		a.junshengaloysius@digipen.edu
\date		10/09/2023
\brief		Contains the definitions of the recreated matrix 3x3 library.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#include "pch.h"
#include "Vector2d.h"
#include "Matrix3x3lib.h"


namespace MATRIXMATH
{
    // Constructors
    Matrix3x3::Matrix3x3()
    {
        // Initialize to the identity matrix
        SetIdentity();
    }

    Matrix3x3::Matrix3x3(const float* pArr)
    {
        for (int i = 0; i < 9; i++)
        {
            m[i] = pArr[i];
        }
    }

    Matrix3x3::Matrix3x3(float _00, float _01, float _02,
        float _10, float _11, float _12,
        float _20, float _21, float _22)
    {
        // Initialize the matrix elements
        m[0] = _00;
        m[1] = _01;
        m[2] = _02;
        m[3] = _10;
        m[4] = _11;
        m[5] = _12;
        m[6] = _20;
        m[7] = _21;
        m[8] = _22;
    }

    // Assignment operator
    Matrix3x3& Matrix3x3::operator=(const Matrix3x3& rhs)
    {
        if (this != &rhs)
        {
            for (int i = 0; i < 9; i++)
            {
                m[i] = rhs.m[i];
            }
        }
        return *this;
    }

    // Multiplication operator
    Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs)
    {
        Matrix3x3 result;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                float sum = 0.0f;
                for (int k = 0; k < 3; k++)
                {
                    sum += lhs(i, k) * rhs(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }

    // Other matrix operations
    VECTORMATH::Vector2D Matrix3x3::operator*(const VECTORMATH::Vector2D& rhs) const
    {
        float x = (m[0] * rhs.x) + (m[1] * rhs.y) + m[2];
        float y = (m[3] * rhs.x) + (m[4] * rhs.y) + m[5];
        return VECTORMATH::Vector2D(x, y);
    }

    void Matrix3x3::SetIdentity()
    {
        // Initialize to the identity matrix
        for (int i = 0; i < 9; i++)
        {
            if (i % 4 == 0)
                m[i] = 1.0f;
            else
                m[i] = 0.0f;
        }
    }

    void Matrix3x3::SetTranslation(float x, float y)
    {
        SetIdentity();
        m[2] = x;
        m[5] = y;
    }

    void Matrix3x3::SetScale(float x, float y)
    {
        SetIdentity();
        m[0] = x;
        m[4] = y;
    }

    void Matrix3x3::SetRotationRad(float angle)
    {
        SetIdentity();
        float cosAngle = cos(angle);
        float sinAngle = sin(angle);
        m[0] = cosAngle;
        m[1] = -sinAngle;
        m[3] = sinAngle;
        m[4] = cosAngle;
    }

    void Matrix3x3::SetRotationDeg(float angle)
    {
        float angleRad = static_cast<float>(angle * (M_PI / 180.0));
        SetRotationRad(angleRad);
    }


    void Matrix3x3::Transpose()
    {
        // Swap non-diagonal elements
        std::swap(m[1], m[3]);
        std::swap(m[2], m[6]);
        std::swap(m[5], m[7]);
    }

    bool Matrix3x3::Inverse(float* determinant)
    {
        // Calculate the determinant
        float det = m[0] * (m[4] * m[8] - m[5] * m[7])
            - m[3] * (m[1] * m[8] - m[2] * m[7])
            + m[6] * (m[1] * m[5] - m[2] * m[4]);

        // If determinant is zero, matrix is not invertible
        if (det == 0.0f)
        {
            if (determinant != nullptr)
                *determinant = 0.0f;
            return false;
        }

        // Calculate the inverse
        float invDet = 1.0f / det;
        Matrix3x3 result;

        result.m[0] = (m[4] * m[8] - m[5] * m[7]) * invDet;
        result.m[1] = (m[2] * m[7] - m[1] * m[8]) * invDet;
        result.m[2] = (m[1] * m[5] - m[2] * m[4]) * invDet;
        result.m[3] = (m[5] * m[6] - m[3] * m[8]) * invDet;
        result.m[4] = (m[0] * m[8] - m[2] * m[6]) * invDet;
        result.m[5] = (m[2] * m[3] - m[0] * m[5]) * invDet;
        result.m[6] = (m[3] * m[7] - m[4] * m[6]) * invDet;
        result.m[7] = (m[1] * m[6] - m[0] * m[7]) * invDet;
        result.m[8] = (m[0] * m[4] - m[1] * m[3]) * invDet;

        // Copy the result to this matrix
        *this = result;

        if (determinant != nullptr)
            *determinant = det;

        return true;
    }

    // Accessors
    float& Matrix3x3::operator()(int row, int col)
    {
        return m[row * 3 + col];
    }

    const float& Matrix3x3::operator()(int row, int col) const
    {
        return m[row * 3 + col];
    }
}