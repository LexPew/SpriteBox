#pragma once
#include "BoundingBox.h"
#include "GameObject.h"

struct CollisionEvent
{
	GameObject* OtherGameObject;
	BoundingBox OtherBoundingBox;
};

