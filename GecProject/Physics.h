#pragma once
#include "RedirectCout.h"
#include "Vector2.h"

class Body
{
	Vector2 Position;
	Vector2 Velocity;
	float Mass{10};
};
class RectangleBody
{
	RectangleBody() = default;
	RectangleBody(const float p_width, const float p_height, const float p_x, const float p_y);
};
class Physics
{
public:
	Physics() = default;

};