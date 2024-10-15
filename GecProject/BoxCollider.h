#pragma once
#include "BoundingBox.h"
#include "Component.h"
#include "GameObject.h"
#include "SpriteRenderer.h"


class BoxCollider : public Component
{
private:


public:
	BoundingBox ColliderBox;

	BoxCollider() = default;

	BoxCollider(const Vector2& p_colliderSize)
	{
		ColliderBox.SetSize(p_colliderSize);
	}



	//~BoxCollider() override;


	void Start() override;
	void Update(const float p_deltaTime) override;
	void Render() override;


};

