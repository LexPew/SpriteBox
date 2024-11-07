#include "Physics.h"

#include "GameObject.h"
#include "IGraphics.h"
#include "SpriteRenderer.h"

void Physics::Start()
{
    TransformComp = Owner->GetComponent<Transform>();
    PhysicsCollider = Owner->GetComponent<Collider>();
    PhysicsCollider->AddListener(this);
}

void Physics::Update(float p_deltaTime)
{
    Velocity.Y -= Gravity * p_deltaTime;

    const Vector2 newPosition = { TransformComp->GetPosition().X + Velocity.X * p_deltaTime, TransformComp->GetPosition().Y + Velocity.Y * p_deltaTime };
    TransformComp->SetPosition(newPosition);

}

void Physics::Render()
{
    //IGraphics::GraphicsHandlerInstance->DrawBounds(SpriteBounds);
}

void Physics::OnCollision(const CollisionEvent& p_collisionEvent)
{

    const BoundingBox otherBoundingBox = p_collisionEvent.OtherBoundingBox;
    const BoundingBox& boundingBox = PhysicsCollider->GetCollisionBounds();
    Vector2 newPosition{ TransformComp->GetPosition().X, TransformComp->GetPosition().Y };

    //Moving right into it 
    if (boundingBox.Right >= otherBoundingBox.Left && Velocity.X > 0)
    {
        Velocity.X = 0;
        newPosition.X = otherBoundingBox.Left - boundingBox.Width - CollisionOffset;
    }
    //Moving left into it 
    else if (boundingBox.Left <= otherBoundingBox.Right && Velocity.X < 0)
    {
        Velocity.X = 0;
        newPosition.X = otherBoundingBox.Right + CollisionOffset;
    }

    //Moving up into it 
    if (boundingBox.Top <= otherBoundingBox.Bottom && Velocity.Y < 0)
    {
        Velocity.Y = 0;

        newPosition.Y = otherBoundingBox.Bottom + CollisionOffset;

    }
    //Moving down into it 
    else if (boundingBox.Bottom >= otherBoundingBox.Top && Velocity.Y > 0)
    {
        Velocity.Y = 0;
        newPosition.Y = otherBoundingBox.Top - boundingBox.Height - CollisionOffset;
    }


    TransformComp->SetPosition(newPosition);

}


