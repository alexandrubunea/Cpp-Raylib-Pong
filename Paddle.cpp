#include "raylib.h"
#include "Utils.cpp"

class Paddle {
private:
	Position position;
	float width, height;
	float acceleration_const, acceleration = 0.0, velocity = 0.0;
	Color color;
public:
	Paddle(Position Pos = Position(0, 0), u32 Width = 0, u32 Height = 0, float Acceleration = 0.0, Color Color = WHITE) {
		width = Width;
		height = Height;
		color = Color;
		acceleration_const = Acceleration;
		position = Pos;
	}
	void render() {
		DrawRectangle(position.x - width / 2, position.y - height / 2, width, height / 2, WHITE);
		DrawRectangle(position.x - width / 2, position.y, width, height / 2, WHITE);
	}
	void controller(s32 key_1, s32 key_2) {
		float dt = GetFrameTime();

		/*
			Paddle is moving up the y axis
		*/
		if (IsKeyDown(key_1))
			acceleration -= acceleration_const;

		/*
			Paddle is moving down the y axis
		*/
		if (IsKeyDown(key_2))
			acceleration += acceleration_const;

		/*
			Motion Equation
		*/
		position.y = position.y + velocity + acceleration * dt * dt * .5f;
		velocity = velocity + acceleration * dt;

		/*
			Limit Movement
		*/
		if (position.y - height / 2 <= 0) {
			velocity = -velocity * .5f;
			position.y = height / 2;
		}

		if (position.y + height / 2 >= GetScreenHeight()) {
			velocity = -velocity * .5f;
			position.y = GetScreenHeight() - height / 2;
		}

		/*
			Reset acceleration value
		*/
		if (IsKeyReleased(key_1) || IsKeyReleased(key_2))
			acceleration = velocity = 0.0;
	}
};