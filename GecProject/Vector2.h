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
	 * 
	 * @return Inverse version of the vector
	 */
	Vector2 operator-() const
	{
		return {-X,-Y};
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
	/**
	 * Compares two vectors to check whether they are equal
	 * @param p_vectorB Vector to compare
	 * @return 
	 */
	bool operator==(const Vector2& p_vectorB) const
	{
		return (X == p_vectorB.X && Y == p_vectorB.Y);
	}

	/**
	 * Divides the vector by the denominator input
	 * @return 
	 */
	Vector2 operator/(const float p_denominator) const
	{
		return { X / p_denominator, Y / p_denominator };
	}

	/**
	 * @return The magnitude of the vector
	 */
	float Magnitude() const
	{
		//|V| = sqrt(a^2 + b^2)

		return sqrt(X * X + Y * Y);
	}

	/**
	 * @return A normalized Vector2
	 */
	Vector2 Normalize() const
	{
		const float mag = Magnitude();
		return { X / mag, Y / mag };
	}

	void Lerp(const Vector2& p_vectorB, const float p_factor) 
	{
		X = (X * (1.0f - p_factor) + (p_vectorB.X * p_factor));
		Y = (Y * (1.0f - p_factor) + (p_vectorB.Y * p_factor));

	}


	/**
	 * Finds the distance between two input vectors
	 * @return Distance in floating point
	 */
	static inline float Distance(const Vector2& p_vectorA, const Vector2& p_vectorB)
	{
		// Correct formula: square of the differences
		const float deltaX = p_vectorA.X - p_vectorB.X;
		const float deltaY = p_vectorA.Y - p_vectorB.Y;

		// Now apply the correct distance formula
		const float distance = sqrt((deltaX * deltaX) + (deltaY * deltaY));

		return distance;
	}

	static inline float Dot(const Vector2& p_vectorA, const Vector2& p_vectorB)
	{
		const float dotProduct = (p_vectorA.X * p_vectorB.X) + (p_vectorA.Y * p_vectorB.Y);
		return dotProduct;
	}

	static inline float Angle(const Vector2& p_vectorA, const Vector2& p_vectorB)
	{
		const float dot = Dot(p_vectorA, p_vectorB);

		const float magA = p_vectorA.Magnitude();
		const float magB = p_vectorB.Magnitude();

		float angle = acos(dot / (magA * magB));

		angle = angle * 180.0f / 3.1415f;
		return angle;
	}

	

};


