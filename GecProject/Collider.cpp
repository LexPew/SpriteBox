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

}

void Collider::CalculateBoundsFromSprite()
{
	const Sprite& sprite = Owner->GetComponent<SpriteRenderer>()->GetSprite();

	Vector2 bounds = IGraphics::GraphicsHandlerInstance->CalculateBounds(sprite);

	Transform* TransformComp = Owner->GetComponent<Transform>();

	float x = TransformComp->GetPosition().X;
	float y = TransformComp->GetPosition().Y;
	float x2 = bounds.X + x;
	float y2 = bounds.Y + y;
	ColliderBox = { y, x, y2, x2 };
}

void Collider::CheckCollision(const Collider& p_otherCollider) const
{
	//This is where we check for collision with another collider
	//First check we can collide via collision layer

	if(GetBitMask() & p_otherCollider.GetBitMask())
	{
		//We are on the same collision layer so check for collisions

	}
	NotifyListeners({ nullptr, p_otherCollider.GetCollisionBounds() });

}

void Collider::AddListener(CollisionListener* p_collisionListener)
{	
	CollisionEventListeners.push_back(p_collisionListener);
}



void Collider::Update(const float p_deltaTime)
{
	ColliderBox.SetPosition(TransformComponent->GetPosition());
}

void Collider::Render()
{
	IGraphics::GraphicsHandlerInstance->DrawBounds(ColliderBox);
}


void Collider::NotifyListeners(const CollisionEvent& p_collisionEvent) const
{
	for (const auto listener : CollisionEventListeners)
	{
		listener->OnCollision(p_collisionEvent);
	}
}
