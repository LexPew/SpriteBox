#include "Physics.h"

#include "GameObject.h"
#include "IGraphics.h"
#include "SpriteRenderer.h"

void Physics::Start()
{
    const Sprite& sprite = Owner->GetComponent<SpriteRenderer>()->GetSprite();


	Vector2 bounds = IGraphics::GraphicsHandlerInstance->CalculateBounds(sprite);

    TransformComp = Owner->GetComponent<Transform>();

    float x = TransformComp->GetPosition().X;
    float y = TransformComp->GetPosition().Y;
    float x2 = bounds.X + x;
    float y2 = bounds.Y + y;
    SpriteBounds = { y, x, y2, x2 };


}

void Physics::Update(const float p_deltaTime)
{


    // Apply gravity to the object's vertical velocity
    Velocity.Y += Gravity * p_deltaTime;

    // Update the object's position using the velocity
    const Vector2 newPosition = { TransformComp->GetPosition().X + Velocity.X, TransformComp->GetPosition().Y + Velocity.Y };
    TransformComp->SetPosition(newPosition);

    SpriteBounds.SetPosition(newPosition);

}

void Physics::Render()
{
    IGraphics::GraphicsHandlerInstance->DrawBounds(SpriteBounds);
}

void Physics::OnCollide(const BoundingBox& p_otherObject)
{
    Vector2 newPosition{ TransformComp->GetPosition().X, TransformComp->GetPosition().Y };

        //Moving right into it 
        if (SpriteBounds.Right >= p_otherObject.Left && Velocity.X > 0)
        {
            Velocity.X = 0;
            newPosition.X = p_otherObject.Left - SpriteBounds.Width - CollisionOffset;
        }
        //Moving left into it 
        else if (SpriteBounds.Left <= p_otherObject.Right && Velocity.X < 0)
        {
            Velocity.X = 0;
            newPosition.X = p_otherObject.Right + CollisionOffset;
        }

        //Moving up into it 
        if (SpriteBounds.Top <= p_otherObject.Bottom && Velocity.Y < 0)
        {
            Velocity.Y = 0;
 
            newPosition.Y = p_otherObject.Bottom + CollisionOffset;
            
        }
        //Moving down into it 
        else if (SpriteBounds.Bottom >= p_otherObject.Top && Velocity.Y > 0)
        {
            Velocity.Y = 0;
            newPosition.Y = p_otherObject.Top - SpriteBounds.Height - CollisionOffset;
        }


        TransformComp->SetPosition(newPosition);
        SpriteBounds.SetPosition(newPosition);
    

}
