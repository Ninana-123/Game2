#pragma once

namespace MATRIXMATH
{
    class Matrix3x3
    {
    public:
        // Constructors
        Matrix3x3();
        Matrix3x3(const float* pArr);
        Matrix3x3(float _00, float _01, float _02,
            float _10, float _11, float _12,
            float _20, float _21, float _22);

        // Copy constructor (default)
        Matrix3x3(const Matrix3x3& rhs) = default;

        // Assignment operators
        Matrix3x3& operator=(const Matrix3x3& rhs);
        Matrix3x3& operator*=(const Matrix3x3& rhs);

        // Multiplication operator
        friend Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs);

        // Other matrix operations
        VECTORMATH::Vector2D operator*(const VECTORMATH::Vector2D& rhs) const;
        void SetIdentity();
        void SetTranslation(float x, float y);
        void SetScale(float x, float y);
        void SetRotationRad(float angle);
        void SetRotationDeg(float angle);
        void Transpose();
        bool Inverse(float* determinant);

        // Accessors
        float& operator()(int row, int col);
        const float& operator()(int row, int col) const;

    private:
        float m[9];
    };
}