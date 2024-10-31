#pragma once

#include <ostream>

#include "Vector2.h"

class BoundingBox
{


public:
	/**
	 * Represents the top left point in space Y,X
	 */
	float Top{0};
	float Left{ 0 };

	/**
	* Represents the bottom right point in space Y,X
	*/
	float Bottom{ 0 };
	float Right{ 0 };

	float Width{ 0 };
	float Height{ 0 };
	BoundingBox() = default;

	/**
	 * Creates a new bounding box with the input dimensions
	 */
	BoundingBox(const float p_top, const float p_left, const float p_bottom, const float p_right)
	{
		Top = p_top;
		Left = p_left;
		Bottom = p_bottom;
		Right = p_right;

		Width = Right - Left;
		Height = Bottom - Top;
	}

	void Translate(const float p_directionX, const float p_directionY)
	{
		Top += p_directionY;
		Bottom += p_directionY;

		Left += p_directionX;
		Right += p_directionX;
	}

	void SetPosition(const Vector2& p_newPosition)
	{
		Top = p_newPosition.Y;
		Left = p_newPosition.X;

		Bottom = p_newPosition.Y + Height;
		Right = p_newPosition.X + Width;
	}

	float GetWidth() const
	{
		return (Right - Left);
	}
	float GetHeight() const
	{
		return (Bottom - Top);
	}

	Vector2 GetPosition() const
	{
		return {Top,Left};
	}

	bool Intersects(const BoundingBox& p_otherBox) const
	{
		if(Left > p_otherBox.Right)
		{
			return false;
		}
		if(Top > p_otherBox.Bottom)
		{
			return  false;
		}
		if(Bottom < p_otherBox.Top)
		{
			return false;
		}
		if(Right < p_otherBox.Left)
		{
			return  false;
		}


		
		// If both checks passed, the boxes intersect
		return true;
	}


};

