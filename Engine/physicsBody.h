#pragma once
#include "vector"
#include "Box.h"
#include "Event.h"
#include <functional>
#include <vector>

#include "GridTrigger.h"

struct PhysicsBody{
	
	GridTrigger* grid_trigger;
	Box<float> hitbox;
	

	PhysicsBody(){
		

	}

};
