#include "SpriteRenderer.h"
#include "IGraphics.h"
#include "GameObject.h"


void SpriteRenderer::Update(const float p_deltaTime)
{
	if (Play && Loop)
	{
		Timer -= p_deltaTime * AnimationSpeedMultiplier;
		if (Timer <= 0)
		{
			Timer = 0.083f; //12FPS
			PlayNextFrame();
		}
	}
}

void SpriteRenderer::Render()
{
	const Transform& transform = *Owner->GetComponent<Transform>();
	GraphicsHandler->RenderSprite(CurrentSprite, transform.GetPosition().X, transform.GetPosition().Y, FrameCounter);
}

void SpriteRenderer::PlayNextFrame()
{
	//If we have reached the last frame reset counter to start frame
	if (FrameCounter >= CurrentSprite.SpriteSheetRows - 1)
	{
		FrameCounter = 0;
	}
	else
	{

		FrameCounter++;
	}
}

void SpriteRenderer::Start()
{
}
