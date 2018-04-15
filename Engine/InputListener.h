#pragma once

#include "Event.h"
#include "Keyboard.h";
#include "Mouse.h"
#include <vector>
#include "Vector.h"

enum KeyCode {
	esc, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12,
	laccent, one, two, three, fout, five, six, seven, eight, nine, zero, minus, eequals, backspace,
	tab, q, w, e, r, t, y, u, i, o, p, lsquarebracket, rsquarebracket, enter,
	caps, a, s, d, f, g, h, j, k, l, semicolon, raccent, backslash,
	lshift, z, x, c, v, b, n, m, comma, dot, forwardslash, rshift,
	lctrl, lwndkey, lalt, space, ralt, rwndkey, options, rctl,
	prntscreen, scrolllock, pasuebreak, insert, home, pageup, delete_, end, pagedown,
	arrowup, arrowleft, arrowdown, arrowright
};

struct InputListener{

	std::vector<EventBox<bool>> keyBoxes;
	EventBox<bool> leftmouse;
	EventBox<bool> rightmouse;
	EventBox<V2i> mousepos;
	Keyboard* keyboard;
	Mouse* mouse;

	InputListener() = default;

	InputListener(Keyboard* keyboard, Mouse* mouse){
		keyBoxes.resize(256);
		this->keyboard = keyboard;
		this->mouse = mouse;
		for(int i = 0; i < 256; i++){
			keyBoxes[i] = new EventBox<bool>(false);
		}
	}

	V2f getWASDVector(){
		V2f wasdVector(0,0);

		wasdVector.x -= keyBoxes['A'].val;
		wasdVector.x += keyBoxes['D'].val;
		wasdVector.y -= keyBoxes['S'].val;
		wasdVector.y += keyBoxes['W'].val;
		return wasdVector;
	}

	V2f getWASDVectorYinversed() {
		V2f wasdVector = getWASDVector();
		wasdVector.y = -wasdVector.y;
		return wasdVector;
	}

	void update(){
		pollMouse();
		pollKeyboard();
	}

	void pollMouse(){
		V2i mouseV(mouse->GetPosX(), mouse->GetPosY());
		mousepos.set(mouseV);

		leftmouse.set(mouse->LeftIsPressed());
		rightmouse.set(mouse->RightIsPressed());
	}

	void pollKeyboard(){
		for(int i = 0; i < 256; i++){
			keyBoxes[i].set(keyboard->KeyIsPressed(i));
		}
	}

	void listenForKeyCombo(std::vector<KeyCode> keys, std::function<void()> callback){
		if(keys.size() == 0){
			return;
		}
		KeyCode lastKey = *keys.end();

		keyBoxes[0].onChange.listen([&](bool val){
			if(val){
				callback();//gaat fout, wordt op het moment gedelete bij einde scope
			}
		});
	}
};

