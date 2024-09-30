#pragma once
#include <string>
#include "Sprite.h"
class IGraphics
{
public:
	virtual ~IGraphics() = 0;

	//Handles creating a sprite
	virtual void CreateSprite(std::string& spriteName) = 0;
	//Handles rendering a sprite at the given location and frame number
	virtual void RenderSprite() = 0;
};

