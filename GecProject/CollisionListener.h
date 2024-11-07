#pragma once
#include "CollisionEvent.h"

class CollisionListener
{
public:
	virtual  void OnCollision(const CollisionEvent& p_collisionEvent) = 0;
};

