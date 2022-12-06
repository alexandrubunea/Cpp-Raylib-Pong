#include "raylib.h"
#include "Utils.cpp"

class Ball {
private:
	Position position;
	float radius;
	float speedX, speedY;
	Color color;
public:
	Ball(Position Pos = Position(0, 0), float Radius = 0, float SpeedX = 0.0, float SpeedY = 0.0, Color Color = WHITE) {
		position = Pos;
		radius = Radius;
		color = Color;
		speedX = SpeedX;
		speedY = SpeedY;
	}
	void render() {
		DrawCircle(position.x, position.y, radius, color);
	}
	void move() {
		float dt = GetFrameTime();

		position.x += speedX * dt;
		position.y += speedY * dt;

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
	void change_speed_x(float SpeedX) {
		speedX = SpeedX;
	}
	void change_speed_y(float SpeedY) {
		speedY = SpeedY;
	}
	void change_position(Position pos) {
		position = pos;
	}
};