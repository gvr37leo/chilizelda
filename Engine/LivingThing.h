#pragma once
#include "Vector.h"
#include "Image.h"
#include "Event.h"
#include "Box.h"

struct LivingThing {
	V2f pos;
	int health;
	int baseHealth;
	float speed;
	Event<int> takeDamage;
	Event<int> die;
	Box<int> collisonBox;
	Image image;
};