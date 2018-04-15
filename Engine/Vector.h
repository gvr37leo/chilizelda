#pragma once
#include <math.h>
#include <functional>

template<typename T, int size>
struct Vector {
	T& x;
	T& y;
	T& z;
	T vals[size] = {};

	Vector() :x(vals[0]), y(vals[1]), z(vals[2]) {
	}

	Vector(T x, T y) :x(vals[0]), y(vals[1]), z(vals[2]) {
		vals[0] = x;
		vals[1] = y;
	}

	Vector(T x, T y, T z) :x(vals[0]), y(vals[1]), z(vals[2]) {
		vals[0] = x;
		vals[1] = y;
		vals[2] = z;
	}

	Vector(T x, T y, T z, T w) :x(vals[0]), y(vals[1]), z(vals[2]) {
		vals[0] = x;
		vals[1] = y;
		vals[2] = z;
		vals[3] = w;
	}

	Vector(const Vector& other) :x(vals[0]), y(vals[1]), z(vals[2]) {
		memcpy(vals, other.vals, sizeof vals);
	}

	Vector& operator= (Vector& other) {
		memcpy(vals, other.vals, sizeof vals);
		return *this;
	}

	Vector& add(const Vector& other) {
		for (int i = 0; i < size; i++) {
			vals[i] += other.vals[i];
		}
		return *this;
	}

	Vector& sub(const Vector& other) {
		for (int i = 0; i < size; i++) {
			vals[i] -= other.vals[i];
		}
		return *this;
	}

	Vector& scale(float scalar) {
		for (int i = 0; i < size; i++) {
			vals[i] *= scalar;
		}
		return *this;
	}

	T dot(const Vector& other)const {
		T sum = 0;
		for (int i = 0; i < size; i++) {
			sum += vals[i] * other.vals[i];
		}
		return sum;
	}

	Vector cross(const Vector& other) {
		return Vector(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
	}

	Vector& normalise() {
		return scale(1 / length());
	}

	float length() {
		float sum = 0;
		for (int i = 0; i < size; i++) {
			sum += vals[i] * vals[i];
		}
		return pow(sum, 0.5);
	}

	Vector lerp(const Vector& other, float weight) {
		return c().add(other.c().sub(*this).scale(weight));
	}

	Vector c() const {
		return *this;
	}

	T& operator[](int index) {
		return vals[index];
	}

	Vector& rotX(float t) {
		float cost = cosf(t);
		float sint = sinf(t);
		T xp = x;
		T yp = y * cost - z * sint;
		T zp = y * sint + z * cost;
		x = xp;
		y = yp;
		z = zp;
		return *this;
	}

	Vector& rotY(float t) {
		float cost = cosf(t);
		float sint = sinf(t);
		T xp = x * cost + z * sint;
		T yp = y;
		T zp = -x * sint + z * cost;
		x = xp;
		y = yp;
		z = zp;
		return *this;
	}

	Vector& rotZ(float t) {
		float cost = cosf(t);
		float sint = sinf(t);
		T xp = x * cost - y * sint;
		T yp = x * sint + y * cost;
		T zp = z;
		x = xp;
		y = yp;
		z = zp;
		return *this;
	}

	Vector<int, size> round() {
		Vector<int, size> v;
		for (int i = 0; i < size; i++) {
			v[i] = std::round(vals[i]);
		}
		return v;
	}

	template<int newsize>
	Vector<T, newsize> resize() {
		Vector<T, newsize> v;
		for (int i = 0; i < newsize; i++) {
			v[i] = vals[i];
		}
		return v;
	}

	void loop(std::function<void(Vector&)> callback){
		Vector<int, size> counter = Vector<int, size>();
		while(counter.compare(*this) == -1){
			callback(counter);
			if(counter.increment(*this)){
				break;
			}
		}
	}

	int compare(Vector& other) {
		for (int i = size - 1; i >= 0; i--) {
			if (vals[i] == other.vals[i]) {
				return 0;
			}
			else if (vals[i] < other.vals[i]) {
				continue;
			}
			else {
				return 1;
			}
		}
		return -1;
	}

	bool operator==(Vector& other){
		for(int i = 0; i < size; i++){
			if(other.vals[i] != vals[i]){
				return false;
			}
		}
		return true;
	}

	bool operator!=(Vector& other) {
		return !(*this == other);
	}

	

	bool increment(Vector comparedTo){
		for(int i = 0; i < size; i++){
			if((vals[i] + 1) < comparedTo.vals[i]){
				vals[i]++;
				return false;
			}else{
				vals[i] = 0;
			}
		}
		return true;
	}

	Vector to(Vector other){
		return other.sub(*this);
	}

	void map(std::function<void(T&,int i)> callback){
		for(int i = 0; i < size; i++){
			callback(vals[i],i);
		}
	}
};

typedef Vector<int, 2> V2i;
typedef Vector<float, 2> V2f;
typedef Vector<int, 3> V3i;
typedef Vector<float, 3> V3f;
typedef Vector<float, 4> V4f;