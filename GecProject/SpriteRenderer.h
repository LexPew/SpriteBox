#pragma once
#include "Component.h"
class SpriteRenderer : public Component
{
private:
	//Default to error
	std::string spriteId{ "Error.png" };
	int spriteSheetRows{ 1 };
	int spriteSheetFrames{ 0 };
	int spriteSheetCurrentFrame{ 0 };

	//Animation 
	bool play{ true };
	bool playOnStart{ true };
	bool loop{ true };

	float animationSpeedMultiplier{ 1 };

	//General Variables
	float timer{ 0 };
	int frameCounter{ 1 };
public:

	//SpriteRenderer() {};
	SpriteRenderer(std::string _SpriteId, int _spriteSheetRows, int _spriteSheetStartFrame)
	{
		UpdateCurrentSprite(_SpriteId, _spriteSheetRows, _spriteSheetStartFrame);
	}

	virtual std::string GetType() override { return "SpriteRenderer"; }
	virtual void Update(float deltaTime) override;
	virtual void Render(IGraphics& graphicsHandler) override;
	bool UpdateCurrentSprite(std::string& _SpriteId, int _spriteSheetRows, int _spriteSheetStartFrame)
	{
		//Checks to ensure we have entered valid data
		if (_SpriteId.empty() || _spriteSheetRows < 1 || _spriteSheetStartFrame < 0)
		{
			return false;
		}
		else
		{
			spriteId = _SpriteId;
			spriteSheetRows = _spriteSheetRows;
			spriteSheetCurrentFrame = _spriteSheetStartFrame;
			return true;
		}

	}
	void SetSpeed(float animationSpeed)
	{
		animationSpeedMultiplier = animationSpeed;
	}
private:
	void PlayNextFrame();

};

