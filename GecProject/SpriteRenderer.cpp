#include "SpriteRenderer.h"
#include "IGraphics.h"
#include "GameObject.h"
void SpriteRenderer::Update(float deltaTime)
{
}

void SpriteRenderer::Render(IGraphics& graphicsHandler)
{
	TransformComponent& transfrom = *owner->GetComponent<TransformComponent>();
	graphicsHandler.RenderSprite(spriteId, transfrom.GetPosition().x, transfrom.GetPosition().y);
}
