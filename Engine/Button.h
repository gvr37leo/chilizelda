#pragma once
#include "Event.h"
#include "UIElement.h"
#include "InputListener.h"
#include <functional>
#include <vector>

struct Button : UIElement{

	Button(){
	
	}

	void addShortCut(std::vector<KeyCode> keys, InputListener* inputlistener, std::function<void()> callback){
		inputlistener->listenForKeyCombo(keys, callback);
	}
};