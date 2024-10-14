#pragma once
#include "Component.h"
#include "Sprite.h"
class IGraphics;
class SpriteRenderer : public Component
{
private:
	/**
	 * Holds all our sprite information in a neat struct
	 */
	Sprite CurrentSprite;


	/**
	 * Pointer to the current GraphicsHandler
	 */
	IGraphics* GraphicsHandler;

	//Animation 
	bool Play{ true };
	bool Loop{ true };

	float AnimationSpeedMultiplier{ 1 };

	//General Variables
	float	Timer{ 0 };
	int		FrameCounter{ 1 };
public:


	/**
	 * Creates a new Sprite renderer with the input sprite
	 * @param p_spriteSettings Sprite's Settings
	 * @param p_graphicsHandler Current Graphics Handler
	 */
	SpriteRenderer(const Sprite& p_spriteSettings, IGraphics* p_graphicsHandler)
	{
		GraphicsHandler = p_graphicsHandler;
		CurrentSprite = p_spriteSettings;
	}

	/**
	* @return The Sprite ID
	*/
	const std::string& GetSpriteId()
	{
		return CurrentSprite.SpriteId;
	}

	/**
	 * Updates the Sprite ID to the input string value
	 * @param p_newSpriteId New Sprite ID
	 */
	void SetSpriteId(const std::string& p_newSpriteId)
	{
		CurrentSprite.SpriteId = p_newSpriteId;
	}

	/**
	 * @return The current animation speed multiplier
	 */
	float GetSpeed() const
	{
		return AnimationSpeedMultiplier;
	}

	/**
	 * Sets the current animation speed multiplier to the input value
	 * @param p_animationSpeed New animation speed multiplier
	 */
	void SetSpeed(const float p_animationSpeed)
	{
		AnimationSpeedMultiplier = p_animationSpeed;
	}

	/**
	 *
	 * @return Whether the animation is currently playing
	 */
	bool GetPlayState() const
	{
		return Play;
	}

	/**
	 * Sets the play state to the input bool
	 * @param p_state Play state
	 */
	void SetPlayState(const bool p_state)
	{
		Play = p_state;
	}
	

	virtual void Start() override;
	virtual void Update(const float p_deltaTime) override;
	virtual void Render() override;

	

private:
	void PlayNextFrame();



};

