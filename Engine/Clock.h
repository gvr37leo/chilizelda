#pragma once
#include <chrono>
#include <functional>
#include <vector>

struct CallInXsecondsRegistration {
	float timeLeft;
	std::function<void()> callback;

	CallInXsecondsRegistration(float timeLeft, std::function<void()> callback) {
		this->timeLeft = timeLeft;
		this->callback = callback;
	}
};

struct PClock{

	std::chrono::time_point<std::chrono::steady_clock> lastDelta;
	std::vector<CallInXsecondsRegistration> callbacks;
	float time = 0;

	PClock(){
		lastDelta = std::chrono::high_resolution_clock::now();
	}

	void updateCallbacks(float delta){
		for(int i = callbacks.size() - 1; i >= 0; i--){
			callbacks[i].timeLeft -= delta;
			if(callbacks[i].timeLeft <= 0){
				callbacks[i].callback();
				callbacks.erase(callbacks.begin(), callbacks.begin() + 1);
			}
		}
	}

	float delta(){
		auto now = std::chrono::high_resolution_clock::now();;
		std::chrono::duration<float> duration = now - lastDelta;
		lastDelta = now;
		float delta = duration.count();
		time += delta;
		return delta;
	}

	void callInXseconds(float seconds, std::function<void()> callback) {
		callbacks.push_back(CallInXsecondsRegistration(seconds, callback));
	}
};

