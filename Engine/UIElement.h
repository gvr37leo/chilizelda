#pragma once
#include "Box.h"
#include "Event.h"


struct UIElement{
	UIElement* parent;
	Box<int> collisionBox;
	EventBox<bool> focused;


	Event<int> onKeyDown;
	Event<int> onKeyUp;
	Event<int> onFocus;
	Event<int> onBlur;
	Event<int> onclick;
	Event<int> mouseEnter;
	Event<int> mouseLeave;

	//Event<int> onInput;
	//Event<int> onChange;
	

	UIElement(){
	
	}

	V2i getPos(){
		return collisionBox.pos;
	}
};