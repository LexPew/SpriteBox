#include "BoxCollider.h"

#include "GameObject.h"

void BoxCollider::Start()
{
	//Attempt to grab collider size from current sprite by default

	const SpriteRenderer* renderer = Owner->GetComponent<SpriteRenderer>();

	if (renderer)
	{
		ColliderBox.SetSize(renderer->GetSprite().SpriteSize);
	}
}

void BoxCollider::Update(const float p_deltaTime)
{
	//Update bounding box position
	ColliderBox.SetPosition(Owner->GetComponent<Transform>()->GetPosition());
	//std::cout << ColliderBox.GetPosition().X + ColliderBox.GetBounds().X << "\n";
}

void BoxCollider::Render()
{
	Component::Render();
}
