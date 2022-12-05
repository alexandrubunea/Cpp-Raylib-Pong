#include "raylib.h"
#include "Utils.cpp"

class Paddle {
private:
	Position position;
	u32 width, height;
	Color color;
public:
	Paddle(Position Pos = Position(0, 0), u32 Width = 0, u32 Height = 0, Color Color = WHITE) {
		width = Width;
		height = Height;
		color = Color;
		position = Pos;
	}
	void render() {
		DrawRectangle(position.x - width / 2, position.y - height / 2, width, height / 2, WHITE);
		DrawRectangle(position.x - width / 2, position.y, width, height / 2, WHITE);
	}
};