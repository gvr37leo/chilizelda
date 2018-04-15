#pragma once
#include <vector>
#include <functional>

struct Stat{
	int val;
	std::vector<std::function<void(int&)>> modifiers;

	int get(){
		int copy = val;
		for each (std::function<void(int&)> modifier in modifiers){
			modifier(copy);
		}
		return copy;
	}
};