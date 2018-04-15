#pragma once
#include "Image.h"
#include "map"

struct TileMap{
	
	Image* mapLayout;
	Image* spriteAtlas;
	V2i spriteSize;
	std::map<V4f, V2i> color2spriteLocation;

	TileMap(Image* mapLayout, Image* spriteAtlas, V2i spriteSize){
		this->spriteAtlas = spriteAtlas;
		this->mapLayout = mapLayout;
		this->spriteSize = spriteSize;
	}

	void registerTile(V4f color,V2i spriteLocation){
		color2spriteLocation[color] = spriteLocation;
	}

	void draw(Graphics& gfx){
		mapLayout->size.loop([&](V2i pos){
			V2i spritelocation = color2spriteLocation[mapLayout->getPixel(pos.x, pos.y)];

		});
	}

};
