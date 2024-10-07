#include "SpriteRenderer.h"
#include "IGraphics.h"
#include "GameObject.h"


void SpriteRenderer::Update(float deltaTime)
{
	if (play && loop)
	{
		timer -= deltaTime * animationSpeedMultiplier;
		if (timer <= 0)
		{
			timer = 0.0833333333; //12FPS
			PlayNextFrame();
		}
	}
}

void SpriteRenderer::Render()
{
	TransformComponent& transfrom = *owner->GetComponent<TransformComponent>();
	graphicsHandler.RenderSprite(spriteId, transfrom.GetPosition().x, transfrom.GetPosition().y, spriteSheetRows,spriteSheetCurrentFrame);
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
