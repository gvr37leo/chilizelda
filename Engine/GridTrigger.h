#pragma once;
#include "Event.h"
#include "Vector.h"
#include "Box.h"
#include <functional>
#include <map>
#include <vector>
#include "TwoDarray.h"

struct GridTrigger{
	
	TwoDarray<std::map<int, std::function<void()>>> triggers;
	std::map<int, Box<int>> handleBoxes;
	V2i granularity;
	Box<int> box;
	int handleCounter = 0;

	GridTrigger(V2i granularity,Box<int> box){
		this->box = box;
		this->granularity = granularity;
		triggers = TwoDarray<std::map<int, std::function<void()>>>(granularity);
	}

	V2i worldPos2GridPos(V2i pos){
		V2i relativePos = box.pos.to(pos);
		relativePos.map([&](int val, int i) { val /= granularity.vals[i];});
		return relativePos;
	}

	//returns handle to use when deafen
	int listen(Box<int> box, std::function<void()> callback){
		handleCounter++;
		handleBoxes[handleCounter] = box;
		box.size.loop([&](V2i pos){
			V2i absPos = pos.c().add(box.size);
			triggers.get(absPos)[handleCounter] = callback;
		});
		return handleCounter;
	}

	void trigger(V2i worldPos){
		auto triggermap = triggers.get(worldPos2GridPos(worldPos));
		for(auto pair : triggermap){
			pair.second();
		}
	}

	void deafen(int handle) {
		Box<int> deafenBox = handleBoxes[handle];

		deafenBox.size.loop([&](V2i pos){
			V2i absPos = pos.c().add(box.size);
			triggers.get(absPos).erase(handle);
		});
	}
};