/******************************************************************************/
/*!
\file		mathLib.cpp
\author		Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807
\par		a.junshengaloysius@digipen.edu
\date		10/09/2023
\brief		Contains the definitions of the recreated vector library.

 */
 /******************************************************************************/

#include "pch.h"
#include "mathLib.h"


namespace VECTORMATH {

    /**************************************************************************/
    /*!
        Initializes the x and y values with the given parameters
     */
     /**************************************************************************/
    Vector2D::Vector2D(float _x, float _y) : x(_x), y(_y) {
    }

    // Assignment operators
    /**************************************************************************/
    /*!
        Adds two Vectors together and returns the modified vector
     */
     /**************************************************************************/
    Vector2D& Vector2D::operator += (const Vector2D& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    /**************************************************************************/
    /*!
        Subtracts two Vectors together and returns the modified vector
     */
     /**************************************************************************/
    Vector2D& Vector2D::operator -= (const Vector2D& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    /**************************************************************************/
    /*!
        Multiplies a vector by a float value rhs and returns the modified vector
     */
     /**************************************************************************/
    Vector2D& Vector2D::operator*=(float rhs) {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    /**************************************************************************/
    /*!
        Divides a vector by a float value rhs and returns the modified vector
     */
     /**************************************************************************/
    Vector2D& Vector2D::operator /= (float rhs) {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    // Unary operator
    /**************************************************************************/
    /*!
        Inverses the values of the vector
     */
     /**************************************************************************/
    Vector2D Vector2D::operator -() const {
        return Vector2D(-x, -y);
    }

    // Binary operators
    /**************************************************************************/
    /*!
        Adds two vectors together and returns the result
     */
     /**************************************************************************/
    Vector2D operator + (const Vector2D& lhs, const Vector2D& rhs) {
        Vector2D result;
        result.x = lhs.x + rhs.x;
        result.y = lhs.y + rhs.y;
        return result;
    }

    /**************************************************************************/
    /*!
        Subtracts two vectors together and returns the result
     */
     /**************************************************************************/
    Vector2D operator - (const Vector2D& lhs, const Vector2D& rhs) {
        Vector2D result;
        result.x = lhs.x - rhs.x;
        result.y = lhs.y - rhs.y;
        return result;
    }

    /**************************************************************************/
    /*!
        Performs scalar multiplication and returns the result
     */
     /**************************************************************************/
    Vector2D operator * (const Vector2D& lhs, float rhs) {
        Vector2D result;
        result.x = lhs.x * rhs;
        result.y = lhs.y * rhs;
        return result;
    }

    /**************************************************************************/
    /*!
        Performs scalar multiplication and returns the result
     */
     /**************************************************************************/
    Vector2D operator * (float lhs, const Vector2D& rhs) {
        Vector2D result;
        result.x = rhs.x * lhs;
        result.y = rhs.y * lhs;
        return result;
    }

    /**************************************************************************/
    /*!
        Performs scalar division and returns the result
     */
     /**************************************************************************/
    Vector2D operator / (const Vector2D& lhs, float rhs) {
        Vector2D result;
        result.x = lhs.x / rhs;
        result.y = lhs.y / rhs;
        return result;
    }

    /**************************************************************************/
    /*!
        In this function, pResult will be the unit vector of pVec0
     */
     /**************************************************************************/
    void Vector2DNormalize(Vector2D& pResult, const Vector2D& pVec0) {
        float magnitude = sqrt((pVec0.x * pVec0.x) + (pVec0.y * pVec0.y));
        if (magnitude > 0) {
            pResult.x = pVec0.x / magnitude;
            pResult.y = pVec0.y / magnitude;
        }
        else {
            // The vector is already normalized when magnitude = 0
            pResult = pVec0;
        }
    }

    /**************************************************************************/
    /*!
        This function returns the length of the vector pVec0
     */
     /**************************************************************************/
    float Vector2DLength(const Vector2D& pVec0) {
        return static_cast<float>(sqrt(pow(pVec0.x, 2) + pow(pVec0.y, 2)));  // Pythagoras
    }

    /**************************************************************************/
    /*!
        This function returns the square of pVec0's length. Avoid the square root
     */
     /**************************************************************************/
    float Vector2DSquareLength(const Vector2D& pVec0) {
        return static_cast<float>(pow(pVec0.x, 2) + pow(pVec0.y, 2));
    }

    /**************************************************************************/
    /*!
        In this function, pVec0 and pVec1 are considered as 2D points.
        The distance between these 2 2D points is returned
     */
     /**************************************************************************/
    float Vector2DDistance(const Vector2D& pVec0, const Vector2D& pVec1) {
        return static_cast<float>(sqrt(pow(pVec0.x - pVec1.x, 2) + pow(pVec0.y - pVec1.y, 2)));
    }

    /**************************************************************************/
    /*!
        In this function, pVec0 and pVec1 are considered as 2D points.
        The squared distance between these 2 2D points is returned.
        Avoid the square root
     */
     /**************************************************************************/
    float Vector2DSquareDistance(const Vector2D& pVec0, const Vector2D& pVec1) {
        return static_cast<float>(pow(pVec0.x - pVec1.x, 2) + pow(pVec0.y - pVec1.y, 2));
    }

    /**************************************************************************/
    /*!
        This function returns the dot product between pVec0 and pVec1
     */
     /**************************************************************************/
    float Vector2DDotProduct(const Vector2D& pVec0, const Vector2D& pVec1) {
        return (pVec0.x * pVec1.x) + (pVec0.y * pVec1.y);
    }

    /**************************************************************************/
    /*!
        This function returns the cross product magnitude
        between pVec0 and pVec1
     */
     /**************************************************************************/
    float Vector2DCrossProductMag(const Vector2D& pVec0, const Vector2D& pVec1) {
        return (pVec0.x * pVec1.y) - (pVec1.x * pVec0.y);
    }

} // namespace VECTORMATH