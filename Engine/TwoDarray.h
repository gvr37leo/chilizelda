#pragma once
#include "Vector.h"
#include <vector>

template<typename T>
struct TwoDarray{
	V2i	size;
	std::vector<T> array;

	TwoDarray() = default;

	TwoDarray(V2i size) {
		this->size = size;
		array.reserve(size.x * size.y);
	}

	T& get(V2i pos){
		return array[index(pos)];
	}

	int index(V2i pos){
		return pos.y * size.x + pos.x;
	}
};