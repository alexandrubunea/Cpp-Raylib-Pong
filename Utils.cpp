#pragma once

typedef unsigned int u32;

struct Position {
	u32 x, y;
	Position(u32 X = 0, u32 Y = 0) {
		x = X;
		y = Y;
	}
};