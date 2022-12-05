#include "raylib.h"
#include "Utils.cpp"

class Ball {
private:
	Position position;
	float radius;
	Color color;
public:
	Ball(Position Pos = Position(0, 0), float Radius = 0, Color Color = WHITE) {
		position = Pos;
		radius = Radius;
		color = Color;
	}
	void render() {
		DrawCircle(position.x, position.y, radius, color);
	}
};