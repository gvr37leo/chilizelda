#pragma once
template<typename T>
T map(T val1, T start1, T stop1 , T start2, T stop2){
	return start2 + (stop2 - start2) * ((val1 - start1) / (stop1 - start1));
}

template<typename T>
void swap(T& a, T& b){
	T temp = a;
	a = b;
	b = temp;
}

template<typename T>
T min(T a, T b){
	if (a < b)return a;
	return b;
}

template<typename T>
T max(T a, T b){
	if (a > b)return a;
	return b;
}

template<typename T>
T clamp(T val, T minv, T maxv){
	return max(min(val, maxv), minv);
}

template<typename T>
bool inRange(T min, T max, T value) {
	if (min > max) {
		swap(min, max);
	}
	return value <= max && value >= min;
}

template<typename T>
bool rangeOverlap(T r1min, T r1max, T r2min, T r2max){
	return r1min <= r2max && r2min <= r1max;
}

