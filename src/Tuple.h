#pragma once

class Tuple {
public:
	float x;
	float y;
	float z;
	float w;

	Tuple(float x, float y, float z, float w);
	bool isPoint();
	bool isVector();
};