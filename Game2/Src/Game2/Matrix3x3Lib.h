#pragma once

namespace MATRIXMATH
{
    class Matrix3x3
    {
    public:
        // Constructors
        /**************************************************************************/
        /*!
        \brief Default constructor that initializes a 3x3 matrix to the identity matrix.

        */
        /**************************************************************************/
        Matrix3x3();

        /**************************************************************************/
        /*!
        \brief Constructor that initializes a 3x3 matrix using an array of 9 floats.

        \param[in] pArr
        A pointer to an array of 9 floats used to initialize the matrix.

        */
        /**************************************************************************/
        Matrix3x3(const float* pArr);

        /**************************************************************************/
        /*!
        \brief Constructor that initializes a 3x3 matrix with individual elements.

        \param[in] _00, _01, _02, _10, _11, _12, _20, _21, _22
            The individual elements of the 3x3 matrix in row-major order.

        */
        /**************************************************************************/
        Matrix3x3(float _00, float _01, float _02,
            float _10, float _11, float _12,
            float _20, float _21, float _22);

        /**************************************************************************/
        /*!
        \brief Copy constructor that creates a new matrix as a copy of an existing one.

        \param[in] rhs
            The matrix to be copied.

        */
        /**************************************************************************/
        Matrix3x3(const Matrix3x3& rhs) = default;

        // Assignment operators
        /**************************************************************************/
        /*!
        \brief Assignment operator that assigns the values of another matrix to this one.

        \param[in] rhs
            The matrix from which values are assigned.

        \return
            A reference to this matrix after assignment.

        */
        /**************************************************************************/
        Matrix3x3& operator=(const Matrix3x3& rhs);


        /**************************************************************************/
        /*!
        \brief Multiplication operator that multiplies two matrices and returns the result.

        \param[in] lhs
            The left-hand side matrix.

        \param[in] rhs
            The right-hand side matrix.

        \return
            The result of multiplying the two matrices.

        */
        /**************************************************************************/
        friend Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs);

        // Other matrix operations
        /**************************************************************************/
        /*!
        \brief Multiplication operator that multiplies the matrix by a 2D vector.

        \param[in] rhs
            The 2D vector to be multiplied with the matrix.

        \return
            The resulting 2D vector after multiplication.

        */
        /**************************************************************************/
        VECTORMATH::Vector2D operator*(const VECTORMATH::Vector2D& rhs) const;

        /**************************************************************************/
        /*!
        \brief Sets the matrix to the identity matrix.

        */
        /**************************************************************************/
        void SetIdentity();

        /**************************************************************************/
        /*!
        \brief Sets the matrix as a translation matrix for the specified translation.

        \param[in] x, y
            The translation values along the x and y axes, respectively.

        */
        /**************************************************************************/
        void SetTranslation(float x, float y);

        /**************************************************************************/
        /*!
        \brief Sets the matrix as a scale matrix for the specified scaling factors.

        \param[in] x, y
            The scaling factors along the x and y axes, respectively.

        */
        /**************************************************************************/
        void SetScale(float x, float y);

        /**************************************************************************/
        /*!
        \brief Sets the matrix as a rotation matrix for the specified angle in radians.

        \param[in] angle
            The rotation angle in radians.

        */
        /**************************************************************************/
        void SetRotationRad(float angle);

        /**************************************************************************/
        /*!
        \brief Sets the matrix as a rotation matrix for the specified angle in degrees.

        \param[in] angle
            The rotation angle in degrees.

        */
        /**************************************************************************/
        void SetRotationDeg(float angle);

        /**************************************************************************/
        /*!
        \brief Transposes the matrix, swapping rows and columns.

        */
        /**************************************************************************/
        void Transpose();

        /**************************************************************************/
        /*!
        \brief Computes the inverse of the matrix and optionally returns the determinant.

        \param[out] determinant
            A pointer to a float where the determinant of the matrix will be stored. Can be nullptr if not needed.

        \return
            True if the matrix is invertible, false if it's singular.

        */
        /**************************************************************************/
        bool Inverse(float* determinant);

        // Accessors/**************************************************************************/
        /*!
        \brief Accesses the elements of the matrix using row and column indices.

        \param[in] row, col
            The indices of the row and column of the matrix element to access.

        \return
            A reference to the matrix element at the specified row and column.

        */
        /**************************************************************************/
        float& operator()(int row, int col);

        /**************************************************************************/
        /*!
        \brief Accesses the elements of the matrix using row and column indices (const version).

        \param[in] row, col
            The indices of the row and column of the matrix element to access.

        \return
            A const reference to the matrix element at the specified row and column.

        */
        /**************************************************************************/
        const float& operator()(int row, int col) const;

    private:
        float m[9];
    };
}