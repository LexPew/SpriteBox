#pragma once

#include <ostream>

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
	void SetSize(const Vector2& p_boundingSize)
	{
		BoundSize = p_boundingSize;
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
		// Get the bounds (position and size) of both boxes
		const auto& otherPos = p_otherBox.GetPosition();
		const auto& otherBounds = p_otherBox.GetBounds();

		// Check for separation on the X axis
		if (Position.X + BoundSize.X < otherPos.X || Position.X > otherPos.X + otherBounds.X)
		{
			return false; // No overlap on the X axis
		}

		// Check for separation on the Y axis
		if (Position.Y + BoundSize.Y < otherPos.Y || Position.Y > otherPos.Y + otherBounds.Y)
		{
			return false; // No overlap on the Y axis
		}

		// If both checks passed, the boxes intersect
		return true;
	}


};

