#pragma once
#include "Image.h"
#include "map"

struct TileMap{
	
	Image* mapLayout;
	Image* spriteAtlas;
	V2i spriteSize;
	std::map<int, V2i> color2spriteLocation;

	TileMap(Image* mapLayout, Image* spriteAtlas, V2i spriteSize){
		this->spriteAtlas = spriteAtlas;
		this->mapLayout = mapLayout;
		this->spriteSize = spriteSize;
	}

	void registerTile(V3i color,V2i spriteLocation){
		color2spriteLocation[colorToInt(color)] = spriteLocation.multiply(spriteSize);
	}

	int colorToInt(V3i color){
		int result = 0;
		result += color.x << 8;
		result += color.y << 8;
		result += color.z << 8;
		return result;
	}

	void draw(Graphics& gfx){
		Box<int> screenMask = gfx.getScreenBox();
		mapLayout->size.loop([&](V2i pos){
			V2i spritelocation = color2spriteLocation[colorToInt(mapLayout->getPixel(pos.x, pos.y).resize<3>())];
			spriteAtlas->draw(gfx, pos.c().multiply(spriteSize), screenMask, Box<int>(spritelocation,spriteSize), spriteAtlas->defaultEffect());
		});
	}

};
