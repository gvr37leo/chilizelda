#include "MainWindow.h"
#include "Game.h"
#include "Image.h"
#include "Player.h"
#include "InputListener.h"
#include "Clock.h"
#include <iostream>
#include <functional>
#include "utils.h"
#include <math.h>
#include "Enemy.h"

 //keyboard and mouseinput system
 //audio
 //clock
 //events
 //tilemap (possibly tilemap editor)
 //collision detection (grid system and box system)
 //primitive collision handling
 //box class
 //combining usefull classes in git repo
 //UI system
 //buttons-shortcuts with text,input,text,anchoring
 //simple ai
 //ability and buff system
 //simple animation system
 //player controlled sprite
 //platformer with enemy that move in weird patterns and shoot

Player* player;
Enemy* enemy;
InputListener* inputListener;
PClock pclock;
float delta = 0;
Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	inputListener = new InputListener(&wnd.kbd, &wnd.mouse);
	player = new Player(V2f(50,50), Image("sprite.bmp"),inputListener);
	enemy = new Enemy(V2f(300, 300), Image("sprite.bmp"),player);
}




void Game::Go(){
	delta = pclock.delta();
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

float movespeed = 500;

void Game::UpdateModel(){
	if(wnd.mouse.LeftIsPressed())
	{
		int x = 8;
	}
	inputListener->update();

	player->update(delta);
	enemy->update(delta);


}

void Game::ComposeFrame(){
	float anim = sinf(pclock.time) * 0.5 + 0.5;
	Box<int> screensize = gfx.getScreenBox();

	
	player->draw(gfx, pclock);
	enemy->image.draw(gfx, enemy->pos.round(), screensize, enemy->image.defaultEffect());

}
