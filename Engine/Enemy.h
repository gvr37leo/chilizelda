#pragma once
#include "LivingThing.h"
#include "Player.h"

struct Enemy : LivingThing{

	Player* target;

	Enemy() = default;

	Enemy(V2f pos, Image image, Player* target) {
		this->pos = pos;
		this->image = image;
		this->target = target;
		speed = 50.0f;
	}

	void update(float delta){

		if(pos != target->pos){
			pos.add(pos.to(target->pos).normalise().scale(speed).scale(delta));
		}
		
	}
};