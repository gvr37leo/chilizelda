#pragma once
#include "Vector.h"
#include "Box.h"
#include "Image.h"

struct Bullet{
	V2f pos;
	V2f vel;
	int damage;
	Image image;
	Box<int> hitbox;
	float timeLeft;

	Bullet() = default;

	Bullet(const V2f pos, const V2f vel, int damage, const Image image, const Box<int> hitbox, float time_left)
		: pos(pos),
		  vel(vel),
		  damage(damage),
		  image(image),
		  hitbox(hitbox),
		  timeLeft(time_left)
	{

	}

	void update(float delta){
		pos.add(vel.c().scale(delta));
		timeLeft -= delta;
	}

	void draw(Graphics& gfx){
		image.draw(gfx, pos.round(), gfx.getScreenBox(), image.defaultEffect());
	}
};