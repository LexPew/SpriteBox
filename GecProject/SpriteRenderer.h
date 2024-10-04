#pragma once
#include "Component.h"
class SpriteRenderer : public Component
{
private:
	//Default to error
	std::string spriteId{ "Attack.png" };
public:
	// Inherited via Component
	virtual std::string GetType() override { return "SpriteRenderer"; }
	virtual void Update(float deltaTime) override;
	virtual void Render(IGraphics& graphicsHandler) override;
};

