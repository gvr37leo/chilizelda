#pragma once
#include "utils.h"
#include "Vector.h"

template<typename T>
struct Box{
	Vector<T, 2> pos;
	Vector<T, 2> size;

	Box() = default;

	Box(Vector<T, 2> pos, Vector<T, 2> size){
		this->pos = pos;
		this->size = size;
	}

	V2f getPoint(V2f relativePos){
		V2f halfsize = size.c().scale(0.5);
		V2f center = pos.add(halfsize);

		halfsize.x *= relativePos.x;
		halfsize.y *= relativePos.y;
		return center.add(halfsize);
	}

	bool isColliding(Box<T>& other){
		for(int i = 0; i < 2; i++){
			if(!rangeOverlap(getEdge(i,false), getEdge(i,true), other.getEdge(i,false), other.getEdge(i,true))){
				return false;
			}
		}
		return true;
	}

	bool isColliding(Vector<float, 2>& point){
		for (int i = 0; i < 2; i++) {
			if (!inRange(getEdge(i, false), getEdge(i, true), point.vals[i])) {
				return false;
			}
		}
		return true;
	}

	bool isColliding(Vector<float, 2>& a, Vector<float, 2>& b) {


		return false;
	}

	T getEdge(int dim,bool takeMax){
		T result = pos[dim];
		if(takeMax){
			result += size[dim];
		}
		return result;
	}
};