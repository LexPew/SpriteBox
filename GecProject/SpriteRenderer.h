#pragma once
#include "Component.h"

class IGraphics;
class SpriteRenderer : public Component
{
private:
	IGraphics& graphicsHandler;
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
	SpriteRenderer(std::string _SpriteId, int _spriteSheetRows, int _spriteSheetStartFrame, IGraphics& _graphicsHandler) : graphicsHandler(_graphicsHandler)
	{
		UpdateCurrentSprite(_SpriteId, _spriteSheetRows, _spriteSheetStartFrame);
	}

	//virtual std::string GetType() override { return "SpriteRenderer"; }
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
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

	//Getters and Setters
	std::string& GetSpriteID()
	{
		return spriteId;
	}
	void SetSpriteID(std::string newSpriteId) {
		spriteId = newSpriteId;
	}
	float GetSpeed()
	{
		return animationSpeedMultiplier;
	}
	void SetSpeed(float animationSpeed)
	{
		animationSpeedMultiplier = animationSpeed;
	}
	bool GetPlayState()
	{
		return play;
	}
	void SetPlayState(bool state)
	{
		play = state;
	}
private:
	void PlayNextFrame();


	// Inherited via Component
	virtual void Start() override;

};

