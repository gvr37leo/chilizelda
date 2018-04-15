#pragma once
#include "Vector.h"
#include "Image.h"
#include "Event.h"
#include "LivingThing.h"
#include "InputListener.h"
#include "Clock.h"
#include "Bullet.h"

struct Player : LivingThing{

	InputListener* inputListener;
	std::vector<Bullet> bullets;

	Player() = default;

	Player(V2f pos_, Image image_, InputListener* inputListener){
		this->pos = pos_;
		this->image = image_;
		speed = 200.0f;
		this->inputListener = inputListener;
		Image bulletImage = Image("sprites/bullet.bmp");
		

		inputListener->leftmouse.onChange.listen([=](bool val){
			if(val){
				bullets.emplace_back(pos.c(), V2f(100, 0), 5, bulletImage, Box<int>(V2i(0, 0), V2i(0, 0)), 3);
			}
		});
	}

	void update(float delta){
		//dust effect
		V2f movementInput = inputListener->getWASDVectorYinversed();
		if (movementInput != V2f(0, 0)) {
			pos.add(movementInput.normalise().scale(speed).scale(delta));
		}
		
		for (auto& bullet : bullets){
			bullet.update(delta);
		}
	}

	void draw(Graphics& gfx, PClock& pclock){
		float anim = sinf(pclock.time) * 0.5 + 0.5;
		image.draw(gfx, pos.round(), gfx.getScreenBox(), image.getBox(), image.chromaKeyEffect(V4i(255,0,220,255)));
		for (auto bullet : bullets)
		{
			bullet.draw(gfx);
		}

	}
};