#pragma once

#include <algorithm>

namespace GEC
{
	class Rectangle
	{
	public:
		int left{ 0 };
		int right{ 0 };
		int top{ 0 };
		int bottom{ 0 };

		Rectangle() = default;
		Rectangle(int l, int r, int t, int b) : left(l), right(r), top(t), bottom(b) {}

		int Width() const { return right - left; }
		int Height() const { return bottom - top; }
		void Translate(int dx, int dy) { left += dx; right += dx; top += dy; bottom += dy; };

		void ClipTo(const Rectangle& other)
		{
			left = std::max(left, other.left);
			right = std::min(right, other.right);
			top = std::max(top, other.top);
			bottom = std::min(bottom, other.bottom);
		}

		bool CompletelyOutside(const Rectangle& other) const
		{
			if (left > other.right)
				return true;
			if (top > other.bottom)
				return true;
			if (right < other.left)
				return true;
			if (bottom < other.top)
				return true;

			return false;
		}

		bool CompletelyInside(const Rectangle& other) const
		{
			if (left < other.left)
				return false;
			if (right > other.right)
				return false;
			if (top < other.top)
				return false;
			if (bottom > other.bottom)
				return false;

			return true;
		}

	};

	inline bool Intersects(const Rectangle& a, const Rectangle& b)
	{
		if (a.left > b.right)
			return false;
		if (a.top > b.bottom)
			return false;
		if (a.right < b.left)
			return false;
		if (a.bottom < b.top)
			return false;
	
		return true;
	}
}
