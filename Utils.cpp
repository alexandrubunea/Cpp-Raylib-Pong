#pragma once

typedef unsigned int u32;
typedef int s32;

struct Position {
	float x, y;
	Position(float X = 0, float Y = 0) {
		x = X;
		y = Y;
	}
};