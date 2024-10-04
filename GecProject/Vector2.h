#pragma once
struct Vector2
{
	float x{ 0 };
	float y{ 0 };

	//Default constructor
	Vector2();
	//Allows input values when constructing
	Vector2(float xInput, float yInput)
	{
		x = xInput;
		y = yInput;
	}

	//Addition operator
	Vector2 operator+(Vector2 const& vectorB)
	{
		return Vector2(x + vectorB.x, y + vectorB.y);
	}
	//Subtraction operator
	Vector2 operator-(Vector2 const& vectorB)
	{
		return Vector2(x - vectorB.x, y - vectorB.y);
	}
	//Multiplication by scalar
	Vector2 operator*(float const scalar)
	{
		return Vector2(x * scalar, y * scalar);
	}
};

