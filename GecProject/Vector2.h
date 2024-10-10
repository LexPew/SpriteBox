#pragma once
struct Vector2
{
	float X{ 0 };
	float Y{ 0 };

	/**
	 * Creates a Vector2 struct with the default values 0,0
	 */
	Vector2() = default;
	/**
	 * Creates a Vector2 struct with the input values
	 */
	Vector2(const float p_xInput, const float p_yInput)
	{
		X = p_xInput;
		Y = p_yInput;
	}

	/**
	 * Adds another Vector to this Vector
	 * @param p_vectorB Vector to add to this
	 * @return Finished operation
	 */
	Vector2 operator+(Vector2 const& p_vectorB) const
	{
		return {X + p_vectorB.X, Y + p_vectorB.Y};
	}

	/**
	 * Subtracts another Vector from this Vector
	 * @param p_vectorB Vector to subtract from this
	 * @return Finished operation
	 */
	Vector2 operator-(Vector2 const& p_vectorB) const
	{
		return {X - p_vectorB.X, Y - p_vectorB.Y};
	}

	/**
	 * Multiplies both axis by the input scalar value
	 * @param p_scalar Multiplier
	 * @return Finished operation
	 */
	Vector2 operator*(float const p_scalar) const
	{
		return { X * p_scalar, Y * p_scalar };
	}
};
