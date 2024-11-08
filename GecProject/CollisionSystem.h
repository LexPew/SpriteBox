#pragma once
#include <vector>

#include "Collider.h"

class CollisionSystem
{
private:
	std::vector<Collider*> Colliders;
public:

	void AddCollider(Collider* p_collider)
	{
		Colliders.push_back(p_collider);
	}

	void Update()
	{
		for(Collider* collider : Colliders)
		{
			collider->Overlapping = false;
		}
		//Loop through each collider and every other collider one ahead
		for (size_t i = 0; i < Colliders.size(); ++i)
		{
			for(size_t j = i + 1; j < Colliders.size(); ++j)
			{
				Collider* colliderA = Colliders[i];
				Collider* colliderB = Colliders[j];
				//Check if both are static as if they are they cant interact with each other
				if(colliderA->GetIsStatic() && colliderB->GetIsStatic())
				{
					continue;
				}
				//Check if they are on the same collision layer
				if(colliderA->GetCollisionLayer() & colliderB->GetCollisionLayer())
				{

					//Check if both bounds are intersecting
					if(colliderA->GetCollisionBounds().Intersects(colliderB->GetCollisionBounds()))
					{
						colliderA->Overlapping = true;
						colliderB->Overlapping = true;
						ResolveCollision(colliderA, colliderB);
					}

				}
			}
		}
	}

	void ResolveCollision(Collider* p_colliderA, Collider* p_colliderB)
	{
		
		p_colliderA->NotifyListeners({ p_colliderB->GetOwner(), p_colliderB->GetCollisionBounds() });
		p_colliderB->NotifyListeners({ p_colliderA->GetOwner(), p_colliderA->GetCollisionBounds() });
	}
};

