#pragma once
#include "Image.h"
#include "Event.h"

struct Buff{
	float baseDuration;
	float timeLeft;
	Image image;
	int id;
	Event<int> start;
	Event<int> tick;
	Event<int> end;

};