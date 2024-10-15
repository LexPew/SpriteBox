#pragma once
#include <string>
#include "Vector2.h"

struct Sprite
{
	std::string SpriteId{"Null"};

	int SpriteSheetRows{ 0 };
	Vector2 SpriteSize{0,0};

	Sprite() = default;

	/**
	 * Creates a new Sprite object with the input values
	 * @param p_spriteId Texture file name in working dir
	 * @param p_spriteSheetRows Number of rows
	 * @param p_spriteSize Size of a single frame, or the whole sprite if not sprite-sheet

	 */
	Sprite(const std::string& p_spriteId, const int p_spriteSheetRows, const Vector2& p_spriteSize)
	{
		SpriteId = p_spriteId;
		SpriteSheetRows = p_spriteSheetRows;
		SpriteSize = p_spriteSize;
	}
};

