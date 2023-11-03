/******************************************************************************/
/*!
\file		Vector2d.h
\author		Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807
\par		a.junshengaloysius@digipen.edu
\date		10/09/2023
\brief		Contains the declarations of the recreated vector library.

 */
 /******************************************************************************/

#pragma once

namespace VECTORMATH
{

	/**************************************************************************/
	/*!
		Defines a union "Vector2D" that can be used to represent 2D vectors or
		points in a 2D space.
	 */
	 /**************************************************************************/
	typedef union Vector2D
	{
	#pragma warning(disable : 4201)
		struct
		{
			float x, y;
		};
	#pragma warning(default : 4201)
		float m[2];

		// Constructors
		/**************************************************************************/
		/*!
		\brief Initializes the x and y components of a Vector2D object.

		\param[in] _x
			The x-coordinate value.

		\param[in] _y
			The y-coordinate value.

		*/
		/**************************************************************************/
		Vector2D() : m{ 0.0f, 0.0f } {}
		Vector2D(float _x, float _y);


		Vector2D& operator=(const Vector2D& rhs) = default;
		Vector2D(const Vector2D& rhs) = default;

		// Assignment operators
		/**************************************************************************/
		/*!
		\brief Adds two Vector2D objects and modifies the calling vector.

		\param[in] rhs
			The Vector2D object to be added.

		\return
			A reference to the modified calling vector.

		*/
		/**************************************************************************/
		Vector2D& operator += (const Vector2D& rhs);

		/**************************************************************************/
		/*!
		\brief Subtracts two Vector2D objects and modifies the calling vector.

		\param[in] rhs
			The Vector2D object to be subtracted.

		\return
			A reference to the modified calling vector.

		*/
		/**************************************************************************/
		Vector2D& operator -= (const Vector2D& rhs);

		/**************************************************************************/
		/*!
		\brief Multiplies a Vector2D object by a scalar and modifies the calling vector.

		\param[in] rhs
			The scalar value to multiply the vector by.

		\return
			A reference to the modified calling vector.

		*/
		/**************************************************************************/
		Vector2D& operator *= (float rhs);

		/**************************************************************************/
		/*!
		\brief Divides a Vector2D object by a scalar and modifies the calling vector.

		\param[in] rhs
			The scalar value to divide the vector by.

		\return
			A reference to the modified calling vector.

		*/
		/**************************************************************************/
		Vector2D& operator /= (float rhs);

		// Unary operators
		/**************************************************************************/
		/*!
		\brief Returns the negation of a Vector2D object.

		\return
			A new Vector2D object with negated x and y components.

		*/
		/**************************************************************************/
		Vector2D operator -() const;

	} Vector2D, Vec2, Point2D, Pt2;


	// Binary operators
	/**************************************************************************/
	/*!
	\brief Adds two Vector2D objects and returns the result.

	\param[in] lhs
		The first Vector2D object.

	\param[in] rhs
		The second Vector2D object.

	\return
		A new Vector2D object containing the sum of the input vectors.

	*/
	/**************************************************************************/
	Vector2D operator + (const Vector2D& lhs, const Vector2D& rhs);

	/**************************************************************************/
	/*!
	\brief Subtracts one Vector2D object from another and returns the result.

	\param[in] lhs
		The Vector2D object to be subtracted from.

	\param[in] rhs
		The Vector2D object to subtract.

	\return
		A new Vector2D object containing the result of the subtraction.

	*/
	/**************************************************************************/
	Vector2D operator - (const Vector2D& lhs, const Vector2D& rhs);

	/**************************************************************************/
	/*!
	\brief Multiplies a Vector2D object by a scalar and returns the result.

	\param[in] lhs
		The Vector2D object to be multiplied.

	\param[in] rhs
		The scalar value to multiply the vector by.

	\return
		A new Vector2D object containing the result of the multiplication.

	*/
	/**************************************************************************/
	Vector2D operator * (const Vector2D& lhs, float rhs);

	/**************************************************************************/
	/*!
	\brief Multiplies a scalar by a Vector2D object and returns the result.

	\param[in] lhs
		The scalar value to multiply the vector by.

	\param[in] rhs
		The Vector2D object to be multiplied.

	\return
		A new Vector2D object containing the result of the multiplication.

	*/
	/**************************************************************************/
	Vector2D operator * (float lhs, const Vector2D& rhs);

	/**************************************************************************/
	/*!
	\brief Divides a Vector2D object by a scalar and returns the result.

	\param[in] lhs
		The Vector2D object to be divided.

	\param[in] rhs
		The scalar value to divide the vector by.

	\return
		A new Vector2D object containing the result of the division.

	*/
	/**************************************************************************/
	Vector2D operator / (const Vector2D& lhs, float rhs);

	/**************************************************************************/
	/*!
	\brief Reflects a vector against a normal vector.

	\param[in] pVec
		The vector to be reflected.

	\param[in] pNormal
		The normal vector used for reflection.

	\return
		A new Vector2D object representing the reflected vector.

	*/
	/**************************************************************************/
	Vector2D Vector2DReflect(const Vector2D& pVec, const Vector2D& pNormal);

	/**************************************************************************/
	/*!
	\brief Rotates a 2D vector by a given angle in radians.

	\param[in] vec
		The 2D vector to be rotated.

	\param[in] angleRadians
		The angle in radians by which the vector should be rotated.

	\return
		A new Vector2D object representing the rotated vector.

	*/
	/**************************************************************************/
	Vector2D Vector2DRotate(const Vector2D& vec, float angleRadians);

	/**************************************************************************/
	/*!
	\brief Swaps the values of two Vector2D objects.

	\param[in,out] vec1
		The first Vector2D object whose values will be swapped with vec2.

	\param[in,out] vec2
		The second Vector2D object whose values will be swapped with vec1.

	*/
	/**************************************************************************/
	void Vector2DSwap(Vector2D& vec1, Vector2D& vec2);

	/**************************************************************************/
	/*!	
	\brief Clamps the vector components to a specified range.

	\param[in,out] vec
		The Vector2D object whose components will be clamped.

	\param[in] minVal
		The minimum allowed value for each component.

	\param[in] maxVal
		The maximum allowed value for each component.

	*/
	/**************************************************************************/
	void Vector2DClamp(Vector2D& vec, float minVal, float maxVal);

	/**************************************************************************/
	/*!
	\brief Calculates the angle in radians between two vectors.

	\param[in] vec1
		The first Vector2D object.

	\param[in] vec2
		The second Vector2D object.

	\return
		The angle in radians between the two input vectors.

	*/
	/**************************************************************************/
	float Vector2DAngleBetween(const Vector2D& vec1, const Vector2D& vec2);

	/**************************************************************************/
	/*!
	\brief Normalizes a vector to unit length.

	\param[in,out] pResult
		The Vector2D object that will store the normalized result.

	\param[in] pVec0
		The Vector2D object to be normalized.

	*/
	/**************************************************************************/
	void Vector2DNormalize(Vector2D& pResult, const Vector2D& pVec0);

	/**************************************************************************/
	/*!
	\brief Calculates the length of a vector.

	\param[in] pVec0
		The Vector2D object whose length will be calculated.

	\return
		The length of the input vector.

	*/
	/**************************************************************************/
	float	Vector2DLength(const Vector2D& pVec0);

	/**************************************************************************/
	/*!
	\brief Calculates the square of the length of a vector.

	\param[in] pVec0
		The Vector2D object whose square length will be calculated.

	\return
		The square of the length of the input vector.

	*/
	/**************************************************************************/
	float	Vector2DSquareLength(const Vector2D& pVec0);

	/**************************************************************************/
	/*!
	\brief Calculates the distance between two points represented by Vector2D objects.

	\param[in] pVec0
		The first Vector2D object representing a point.

	\param[in] pVec1
		The second Vector2D object representing a point.

	\return
		The Euclidean distance between the two points.

	*/
	/**************************************************************************/
	float	Vector2DDistance(const Vector2D& pVec0, const Vector2D& pVec1);

	/**************************************************************************/
	/*!
	\brief Calculates the square of the distance between two points represented by Vector2D objects.

	\param[in] pVec0
		The first Vector2D object representing a point.

	\param[in] pVec1
		The second Vector2D object representing a point.

	\return
		The square of the Euclidean distance between the two points.

	*/
	/**************************************************************************/
	float	Vector2DSquareDistance(const Vector2D& pVec0, const Vector2D& pVec1);

	/**************************************************************************/
	/*!
	\brief Calculates the dot product between two Vector2D objects.

	\param[in] pVec0
		The first Vector2D object.

	\param[in] pVec1
		The second Vector2D object.

	\return
		The dot product of the two input vectors.

	*/
	/**************************************************************************/
	float	Vector2DDotProduct(const Vector2D& pVec0, const Vector2D& pVec1);

	/**************************************************************************/
	/*!
	\brief Calculates the magnitude of the cross product between two Vector2D objects.

	\param[in] pVec0
		The first Vector2D object.

	\param[in] pVec1
		The second Vector2D object.

	\return
		The magnitude of the cross product between the two input vectors.

	*/
	/**************************************************************************/
	float	Vector2DCrossProductMag(const Vector2D& pVec0, const Vector2D& pVec1);

	/**************************************************************************/
	/*!
	\brief Set the values of a 2D vector with the specified x and y components.

	\param[in] vec
	A reference to the 2D vector to be modified.

	\param[in] x
	The new x-component value.

	\param[in] y
	The new y-component value.

	*/
	/**************************************************************************/
	void setVector2D(Vector2D& vec, float x, float y);

	/**************************************************************************/
	/*!
	\brief Get the components of a 2D vector and store them in the specified variables.

	\param[in] vec
	A constant reference to the 2D vector from which to retrieve the components.

	\param[out] x
	A reference to store the x-component of the vector.

	\param[out] y
	A reference to store the y-component of the vector.

	*/
	/**************************************************************************/
	void getVector2D(const Vector2D& vec, float& x, float& y);

	/**************************************************************************/
	/*!
	\brief Rotate a 2D vector by the specified angle in radians.

	\param[in] vec
	A reference to the 2D vector to be rotated.

	\param[in] angleRadians
	The angle in radians by which to rotate the vector.

	*/
	/**************************************************************************/
	void rotateVector2D(Vector2D& vec, float angleRadians);
}