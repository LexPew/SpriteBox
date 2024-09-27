#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
class Animation
{
	//Holds the sprite sheet texture for the animation
	//The target sprite to display the animation on
	//Update function to loop through the animation based either on fps or by timeframe(pass deltaTime)
	//Speed var, etc

private:
	//Sprite Variables

	sf::Texture* spriteSheet{nullptr};
	sf::Sprite* targetSprite{nullptr};

	//Sprite Sheet Variables

	float spriteSizeX{ 0 };
	float spriteSizeY{ 0 };

	int sheetRows{ 0 };

	//Animation Variables
	bool play{ true };
	bool playOnStart{ true };
	bool loop		{ true };

	float animationSpeedMultiplier{ 1 };

	//General Variables
	float timer{ 0 };
	int frameCounter{ 1 };
private:

public:
	Animation()
	{

	}
	Animation(sf::Texture* spriteSheetTexture, sf::Sprite* sprite, int rows)
	{
		targetSprite = sprite;
		spriteSheet = spriteSheetTexture;

		spriteSizeX = spriteSheet->getSize().x;
		spriteSizeY = (spriteSheet->getSize().y / rows);

		sheetRows = rows;

		targetSprite->setTexture(*spriteSheet);
		targetSprite->setTextureRect(sf::IntRect(0, 0, spriteSizeX, spriteSizeY));
	}

	void PlayNextFrame()
	{
		//If we have reached the last frame reset counter to start frame
		if (frameCounter >= sheetRows)
		{
			frameCounter = 1;
		}
		else
		{

			targetSprite->setTextureRect(sf::IntRect(0, spriteSizeY * frameCounter, spriteSizeX, spriteSizeY));
			frameCounter++;
		}

	}
	void Update(float deltaTime)
	{
		if(play && loop)
		{
			timer -= deltaTime * animationSpeedMultiplier;
			if (timer <= 0)
			{
				timer = 0.0833333333; //12FPS
				PlayNextFrame();
			}
		}
	}
	void SetSpeed(float animationSpeed)
	{
		animationSpeedMultiplier = animationSpeed;
	}
};

