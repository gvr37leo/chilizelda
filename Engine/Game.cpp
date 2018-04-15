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
#include "TileMap.h"
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
TileMap* tilemap;
PClock pclock;
float delta = 0;
Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	inputListener = new InputListener(&wnd.kbd, &wnd.mouse);
	player = new Player(V2f(50,50), Image("sprites/player.bmp"),inputListener);
	enemy = new Enemy(V2f(300, 300), Image("sprite.bmp"),player);
	tilemap = new TileMap(new Image("sprites/testLand.bmp"),new Image("sprites/sideViewGroundTileMap.bmp"),V2i(32,32));

	tilemap->registerTile(V3i(255,255,255), V2i(0, 0));//white
	tilemap->registerTile(V3i(182,255,0), V2i(1, 0));//lightgreen
	tilemap->registerTile(V3i(0,127,14), V2i(0, 1));//darkgreen
	tilemap->registerTile(V3i(0,0,0), V2i(1, 1));//black
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

	tilemap->draw(gfx);
	player->draw(gfx, pclock);
	enemy->image.draw(gfx, enemy->pos.round(), screensize, enemy->image.getBox(), enemy->image.defaultEffect());

}
