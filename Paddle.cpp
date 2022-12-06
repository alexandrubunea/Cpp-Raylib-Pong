#include "raylib.h"
#include "Utils.cpp"

class Paddle {
private:
	Position position;
	float width, height;
	float speed;
	Color color;
	Rectangle rec;
public:
	Paddle(Position Pos = Position(0, 0), u32 Width = 0, u32 Height = 0, float Speed = 0.0, Color Color = WHITE) {
		width = Width;
		height = Height;
		color = Color;
		speed = Speed;
		position = Pos;
		rec = Rectangle{ position.x - width / 2, position.y - height / 2, width, height };
	}
	void render() {
		DrawRectangleRec(rec, color);
	}
	void controller(s32 key_1, s32 key_2) {
		float dt = GetFrameTime();

		/*
			Paddle is moving up the y axis
		*/
		if (IsKeyDown(key_1))
			position.y -= speed * dt;

		/*
			Paddle is moving down the y axis
		*/
		if (IsKeyDown(key_2))
			position.y += speed * dt;

		/*
			Limit Movement
		*/
		if (position.y - height / 2 <= 0)
			position.y = height / 2;

		if (position.y + height / 2 >= GetScreenHeight())
			position.y = GetScreenHeight() - height / 2;

		/*
			Update Rectangle
		*/
		rec = Rectangle{ position.x - width / 2, position.y - height / 2, width, height };
	}
	Position get_position() {
		return position;
	}
	Rectangle get_rec() {
		return rec;
	}
};