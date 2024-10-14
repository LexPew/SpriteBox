#pragma once

#include "Vector2.h"

class BoundingBox
{
private:
	Vector2 Position{ 0,0 };

	Vector2 BoundSize{ 0,0 };

public:

	BoundingBox() = default;

	BoundingBox(const Vector2& p_position, const Vector2& p_boundsSize)
	{
		Position = p_position;

		BoundSize = p_boundsSize;
	}

	void SetPosition(const Vector2& p_newPosition);

	const Vector2& GetBounds() const
	{
		return BoundSize;
	}

	const Vector2& GetPosition() const
	{
		return Position;
	}

	bool Intersects(const BoundingBox& p_otherBox) const
	{
		if(Position.X > p_otherBox.GetBounds().X)
		{
			return false; //To the right of the other box
		}
		if(Position.Y > p_otherBox.GetBounds().Y)
		{
			return false; //Below the other box
		}
		if (BoundSize.X < p_otherBox.GetPosition().X)
		{
			return false; //To the left of the other box
		}
		if(BoundSize.Y < p_otherBox.GetBounds().Y)
		{
			return false; // Above the other box
		}

		return true;
	}
};

