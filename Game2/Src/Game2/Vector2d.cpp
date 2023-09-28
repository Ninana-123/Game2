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
#include <cmath>
#include <algorithm>
#include "Vector2d.h"

template <typename T>
T customMin(T a, T b) {
    return (a < b) ? a : b;
}

template <typename T>
T customMax(T a, T b) {
    return (a > b) ? a : b;
}

// Custom clamp function to ensure a value falls within a specified range
template <typename T>
T customClamp(T value, T minValue, T maxValue) {
    return customMin(customMax(value, minValue), maxValue);
}


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

    // Reflects a vector pVec against the normal vector
    Vector2D Vector2DReflect(const Vector2D& pVec, const Vector2D& pNormal) {
        // R = V - 2 * (V dot N) * N
        float dotProduct = Vector2DDotProduct(pVec, pNormal);
        Vector2D reflection = pVec - (2.0f * dotProduct * pNormal);
        return reflection;
    }

    // Rotates a 2D vector by a given angle in radians
    Vector2D Vector2DRotate(const Vector2D& vec, float angleRadians) {
        float cosA = std::cos(angleRadians);
        float sinA = std::sin(angleRadians);
        return Vector2D(vec.x * cosA - vec.y * sinA, vec.x * sinA + vec.y * cosA);
    }

    // Swaps the values of two Vector2D objects
    void Vector2DSwap(Vector2D& vec1, Vector2D& vec2) {
        Vector2D temp = vec1;
        vec1 = vec2;
        vec2 = temp;
    }

    // Clamps the vector components to a specified range
    void Vector2DClamp(Vector2D& vec, float minVal, float maxVal) {
        vec.x = customMin(customMax(vec.x, minVal), maxVal);
        vec.y = customMin(customMax(vec.y, minVal), maxVal);
    }

    // Calculates the angle in radians between two vectors
    float Vector2DAngleBetween(const Vector2D& vec1, const Vector2D& vec2) {
        float dotProduct = Vector2DDotProduct(vec1, vec2);
        float magnitude1 = Vector2DLength(vec1);
        float magnitude2 = Vector2DLength(vec2);

        // Ensure the denominators are not zero (avoid division by zero)
        if (magnitude1 > 0 && magnitude2 > 0) {
            float cosTheta = dotProduct / (magnitude1 * magnitude2);
            return static_cast<float>(std::acos(static_cast<double>(customClamp(cosTheta, -1.0f, 1.0f))));
        }
        else {
            // Handle zero-length vectors or other invalid inputs
            return 0.0f; // You can choose an appropriate value for this case
        }
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
        float xSquared = static_cast<float>(pow(pVec0.x, 2));
        float ySquared = static_cast<float>(pow(pVec0.y, 2));
        float squaredLength = xSquared + ySquared;
        float length = sqrt(squaredLength);
        return length;
    }

    /**************************************************************************/
    /*!
        This function returns the square of pVec0's length. Avoid the square root
     */
     /**************************************************************************/
    float Vector2DSquareLength(const Vector2D& pVec0) {
        float xSquared = static_cast<float>(pow(pVec0.x, 2));
        float ySquared = static_cast<float>(pow(pVec0.y, 2));
        float squaredLength = xSquared + ySquared;
        return squaredLength;
    }

    /**************************************************************************/
    /*!
        In this function, pVec0 and pVec1 are considered as 2D points.
        The distance between these 2 2D points is returned
     */
     /**************************************************************************/
    float Vector2DDistance(const Vector2D& pVec0, const Vector2D& pVec1) {
        float deltaX = pVec0.x - pVec1.x;
        float deltaY = pVec0.y - pVec1.y;
        float squaredDistance = static_cast<float>(pow(deltaX, 2) + pow(deltaY, 2));
        float distance = sqrt(squaredDistance);
        return distance;
    }

    /**************************************************************************/
    /*!
        In this function, pVec0 and pVec1 are considered as 2D points.
        The squared distance between these 2 2D points is returned.
        Avoid the square root
     */
     /**************************************************************************/
    float Vector2DSquareDistance(const Vector2D& pVec0, const Vector2D& pVec1) {
        float deltaX = pVec0.x - pVec1.x;
        float deltaY = pVec0.y - pVec1.y;
        float squaredDistance = static_cast<float>(pow(deltaX, 2) + pow(deltaY, 2));
        return squaredDistance;
    }


    /**************************************************************************/
    /*!
        This function returns the dot product between pVec0 and pVec1
     */
     /**************************************************************************/
    float Vector2DDotProduct(const Vector2D& pVec0, const Vector2D& pVec1) {
        float dotProductX = pVec0.x * pVec1.x;
        float dotProductY = pVec0.y * pVec1.y;
        float dotProduct = dotProductX + dotProductY;
        return dotProduct;
    }

    /**************************************************************************/
    /*!
        This function returns the cross product magnitude
        between pVec0 and pVec1
     */
     /**************************************************************************/
    float Vector2DCrossProductMag(const Vector2D& pVec0, const Vector2D& pVec1) {
        float crossProductX = pVec0.x * pVec1.y;
        float crossProductY = pVec1.x * pVec0.y;
        float crossProductMagnitude = crossProductX - crossProductY;
        return crossProductMagnitude;
    }

} // namespace VECTORMATH