#pragma once
#include <string>

#include "Rect.h"
#include "Vector2.h"

struct Sprite
{
	std::string SpriteId{"Null"};

	int SpriteSheetRows{ 0 };
	Rect SpriteBounds{ 0,0,0,0 };

	Sprite() = default;

	/**
	 * Creates a new Sprite object with the input values
	 * @param p_spriteId Texture file name in working dir
	 * @param p_spriteSheetRows Number of rows
	 */
	Sprite(const std::string& p_spriteId, const int p_spriteSheetRows)
	{
		SpriteId = p_spriteId;
		SpriteSheetRows = p_spriteSheetRows;
	}
};

