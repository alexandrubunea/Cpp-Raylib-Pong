#include "raylib.h"
#include "Utils.cpp"

class Ball {
private:
	Position position;
	float radius;
	float speedX, speedY;
	float acceleration = 1.0, acceleration_const;
	Color color;
public:
	Ball(Position Pos = Position(0, 0), float Radius = 0, float Acceleration = 0.0, float SpeedX = 0.0, float SpeedY = 0.0, Color Color = WHITE) {
		position = Pos;
		radius = Radius;
		color = Color;
		speedX = SpeedX;
		speedY = SpeedY;
		acceleration_const = Acceleration;
	}
	void render() {
		DrawCircle(position.x, position.y, radius, color);
	}
	void move() {
		float dt = GetFrameTime();

		position.x += speedX * acceleration * dt;
		position.y += speedY * acceleration * dt;

		/*
			Border Bouncing
		*/
		if (position.y + radius >= GetScreenHeight()) {
			position.y = GetScreenHeight() - radius;
			speedY = -speedY;
		}
		if (position.y - radius <= 0) {
			position.y = radius;
			speedY = -speedY;
		}
	}
	Position get_position() {
		return position;
	}
	float get_speed_x() {
		return speedX;
	}
	float get_speed_y() {
		return speedY;
	}
	void change_speed(float SpeedX, float SpeedY) {
		speedX = SpeedX;
		speedY = SpeedY;
	}
	void change_position(Position pos) {
		position = pos;
	}
	void increase_acceleration() {
		acceleration += acceleration_const;
	}
	void reset_acceleration() {
		acceleration = 1.0;
	}
};