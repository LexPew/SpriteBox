#pragma once
#include "Rect.h"
#include "GameObject.h"

struct CollisionEvent
{
	GameObject* OtherGameObject;
	Rect OtherBoundingBox;
};

