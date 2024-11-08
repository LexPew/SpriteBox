#include "Collider.h"

#include "IGraphics.h"
#include "SpriteRenderer.h"


void Collider::Start()
{
	TransformComponent = Owner->GetComponent<Transform>();
	if (Owner->GetComponent<SpriteRenderer>())
	{
		CalculateBoundsFromSprite();
	}
	ColliderBox.SetPosition(TransformComponent->GetPosition());
	ColliderBox2 = { ColliderBox.Width, ColliderBox.Height, TransformComponent->GetPosition().X, TransformComponent->GetPosition().Y, 10, true, IsStatic };

}

void Collider::CalculateBoundsFromSprite()
{
	const Sprite& sprite = Owner->GetComponent<SpriteRenderer>()->GetSprite();

	const Vector2 bounds = IGraphics::GraphicsHandlerInstance->CalculateBounds(sprite);

	float x = TransformComponent->GetPosition().X;
	float y = TransformComponent->GetPosition().Y;
	float x2 = bounds.X + x;
	float y2 = bounds.Y + y;
	ColliderBox = { y, x, y2, x2 };
}




void Collider::Update(const float p_deltaTime)
{
	TransformComponent->SetPosition({ ColliderBox2.getPosition().x, ColliderBox2.getPosition().y });
	ColliderBox.SetPosition(TransformComponent->GetPosition());
}


void Collider::Render()
{
	IGraphics::GraphicsHandlerInstance->DrawBounds(ColliderBox, Overlapping);
}


//Events
void Collider::AddListener(CollisionListener* p_collisionListener)
{
	CollisionEventListeners.push_back(p_collisionListener);
}
void Collider::NotifyListeners(const CollisionEvent& p_collisionEvent) const
{
	for (const auto listener : CollisionEventListeners)
	{
		listener->OnCollision(p_collisionEvent);
	}
}
