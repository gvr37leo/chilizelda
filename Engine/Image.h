#pragma once

#include "PColor.h"
#include <string>
#include <Windows.h>
#include <fstream>
#include "Graphics.h"
#include "Vector.h"
#include "Box.h"
#include  "Clock.h"

struct Image{
	V2i size;
	V4i* pixels;

	Image() = default;

	Image(std::string string){
		read(string);
	}

	Image(int width, int height){
		this->size.x = width;
		this->size.y = height;
		this->pixels = new V4i[width * height];
	}

	Box<int> getBox(){
		return Box<int>(V2i(0,0),size);
	}

	int index(int x, int y) {
		return y * size.x + x;
	}

	void putPixel(int x, int y, V4i color){
		pixels[index(x, y)] = color;
	}

	V4i& getPixel(int x, int y){
		return pixels[index(x, y)];
	}

	void read(std::string filename){
		BITMAPFILEHEADER bmfh;
		std::ifstream file(filename, std::ios::binary);
		file.read(reinterpret_cast<char*>(&bmfh), sizeof(bmfh));

		BITMAPINFOHEADER bmih;
		file.read(reinterpret_cast<char*>(&bmih), sizeof(bmih));

		size.x = bmih.biWidth;
		size.y = bmih.biHeight;

		pixels = new V4i[size.x * size.y];
		file.seekg(bmfh.bfOffBits);
		int padding = (4 - (size.x * 3) % 4) % 4;


		for(int y = size.y - 1; y >= 0; y--){
			for (int x = 0; x < size.x; x++){
				int b = file.get();
				int g = file.get();
				int r = file.get();

				putPixel(x, y, V4i(r,g,b, 255));
			}
			file.seekg(padding, std::ios::cur);
		}
	}

	void write(std::string string){
	
	}

	void draw(Graphics& gfx, V2i pos, Box<int> mask,Box<int> subregion, std::function<V4i(V2i)> effect) {
		V2i skip = pos.c().to(mask.pos);
		V2i botrightOfMask = mask.pos.c().add(mask.size);
		V2i botRightOfImage = pos.c().add(size);
		V2i stop = botrightOfMask.to(botRightOfImage);

		for (int i = 0; i < 2; i++) {//clamp skip and stop vectors to positive range 0 and up
			skip[i] = max(skip[i], 0);
			stop[i] = max(stop[i], 0);
		}

		subregion.size.c().sub(stop.c().add(skip)).loop([&](V2i& localPosUnskipped) {
			V2i localPos = localPosUnskipped.c().add(skip);
			V2i absolutePos = localPos.c().add(pos);
			V4i pixel = effect(localPos.c().add(subregion.pos));
			if(pixel.vals[3] > 0.1f){
				gfx.PutPixel(absolutePos.x, absolutePos.y, pixel.x, pixel.y , pixel.z);
			}
		});
	}

	/*void scale(int amount){
		V2i newsize = size.c().scale(amount);
		V4f* newpixels = new V4f[newsize.x * newsize.y];
		size.loop([&](V2i pos){
			V2i scaledPos = pos.c().scale(amount);
			int index = newsize.x * pos.x + pos.y;
			newpixels[index]
		});

	}*/

	std::function<V4i(V2i)> defaultEffect(){
		return [&](V2i pos){
			return getPixel(pos.x, pos.y);
		};
	}

	//std::function<V4i(V2i)> inverseEffect(PClock& pclock) {
	//	return [&](V2i pos) {
	//		V4f pixel = getPixel(pos.x, pos.y);
	//		V4f reverse = V4f(1, 1, 1, 1).sub(pixel);

	//		return pixel.lerp(reverse,sinf(pclock.time) * 0.5 + 0.5);
	//	};
	//}

	std::function<V4i(V2i)> chromaKeyEffect(V4i chroma) {
		return [&](V2i pos) {
			V4i pixel = getPixel(pos.x, pos.y);
			if(chroma == pixel){
				return V4i(0, 0, 0, 0);
			}
			return pixel;
		};
		
	}
};