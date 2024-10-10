#include "SpriteRenderer.h"
#include "IGraphics.h"
#include "GameObject.h"


void SpriteRenderer::Update(const float p_deltaTime)
{
	if (play && loop)
	{
		timer -= p_deltaTime * animationSpeedMultiplier;
		if (timer <= 0)
		{
			timer = 0.0833333333; //12FPS
			PlayNextFrame();
		}
	}
}

void SpriteRenderer::Render()
{
	Transform& transfrom = *Owner->GetComponent<Transform>();
	graphicsHandler.RenderSprite(spriteId, transfrom.GetPosition().X, transfrom.GetPosition().Y, spriteSheetRows,spriteSheetCurrentFrame);
}

void SpriteRenderer::PlayNextFrame()
{
	//If we have reached the last frame reset counter to start frame
	if (spriteSheetCurrentFrame >= spriteSheetRows - 1)
	{
		spriteSheetCurrentFrame = 0;
	}
	else
	{

		spriteSheetCurrentFrame++;
	}
}

void SpriteRenderer::Start()
{
}
