#pragma once
#include <atomic>

class CollisionLayer
{
public:
	enum CollisionLayers : std::uint8_t
	{
		Default = 1, //0010
		Player = 1, //0010
		Enemy = 3, //0011

	};
};
