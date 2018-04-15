#pragma once
#include <functional>
#include <vector>

template<typename T>
struct Event{
	std::vector<std::function<void(T)>>* callbacks;

	Event(){
		callbacks = new std::vector<std::function<void(T)>>();
	}

	void listen(std::function<void(T)> callback){
		callbacks->push_back(callback);
	}

	void trigger(T val){
		for each (std::function<void(T)> callback in *callbacks){
			callback(val);
		}
	}
};

template<typename T>
struct EventBox{
	Event<T> onChange = Event<T>();
	Event<T> onOldChange = Event<T>();
	Event<T> onClear = Event<T>();
	T val;
	bool isSet = false;

	EventBox() = default;

	EventBox(T val) {
		this->val = val;
		isSet = true;
	}

	T get(){
		return val;
	}

	void set(T newval){
		T old = val;
		val = newval;
		if(old != val || isSet == false){
			isSet = true;
			onChange.trigger(newval);
			onOldChange.trigger(old);
		}
	}

	void clear(){
		isSet = false;
		onClear.trigger(0);
	}
};