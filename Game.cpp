#include <cmath>
#include "raylib.h"
#include "Utils.cpp"
#include "Paddle.cpp"
#include "Ball.cpp"

const float	PADDLE_WIDTH = 20.0;
const float	PADDLE_HEIGHT = 100.0;
const float	PADDLE_SPEED = 500.0;
const Color	PADDLE_COLOR = WHITE;

const float	BALL_RADIUS	= 5.0;
const float BALL_SPEED_X = 300.0;
const float BALL_SPEED_Y = 300.0;
const float BALL_ACCELERATION = .2;
const Color	BALL_COLOR = WHITE;

const float MAX_BOUNCE_ANGLE = 45.0;

class Game {
private:
	u32 height, width;
	Paddle player_one, player_two;
	Ball ball;

	void init_game() {
		InitWindow(width, height, "Pong");
		SetWindowState(FLAG_VSYNC_HINT);

		Position player_one_position, player_two_position;

		player_one_position = Position(PADDLE_WIDTH * 2, GetScreenHeight() / 2);
		player_two_position = Position(GetScreenWidth() - PADDLE_WIDTH * 2, GetScreenHeight() / 2);

		player_one = Paddle(player_one_position, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED, PADDLE_COLOR);
		player_two = Paddle(player_two_position, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED, PADDLE_COLOR);

		Position ball_position = Position(GetScreenWidth() / 2, GetScreenHeight() / 2);

		ball = Ball(ball_position, BALL_RADIUS, BALL_ACCELERATION, BALL_SPEED_X, BALL_SPEED_Y, BALL_COLOR);

		loop();
	}
	void gameplay() {
		player_one.controller(KEY_W, KEY_S);
		player_two.controller(KEY_UP, KEY_DOWN);

		ball.move();

		/*
			Collisions between the paddles and the ball
		*/
		if (check_ball_paddle_collision(ball, player_one) && ball.get_speed_x() < 0) {
			float distance = player_one.get_position().x - ball.get_position().x;
			float ratio = distance / (PADDLE_WIDTH / 2);
			float bounceAngle = ratio * MAX_BOUNCE_ANGLE;

			ball.change_speed(BALL_SPEED_X * cos(bounceAngle), -(BALL_SPEED_Y * sin(bounceAngle)));

			ball.increase_acceleration();
		}
		if (check_ball_paddle_collision(ball, player_two) && ball.get_speed_x() > 0) {
			float distance = player_one.get_position().x - ball.get_position().x;
			float ratio = distance / (PADDLE_WIDTH / 2);
			float bounceAngle = ratio * MAX_BOUNCE_ANGLE;

			ball.change_speed(-(BALL_SPEED_X * cos(bounceAngle)), -(BALL_SPEED_Y * sin(bounceAngle)));

			ball.increase_acceleration();
		}

		/*
			Check if it was a score
		*/
		if (ball.get_position().x - BALL_RADIUS <= 0) {
			ball.change_position(Position(GetScreenWidth() / 2, GetScreenHeight() / 2));
			ball.change_speed(-BALL_SPEED_X, BALL_SPEED_Y);
			ball.reset_acceleration();
		}
		if (ball.get_position().x + BALL_RADIUS >= GetScreenWidth()) {
			ball.change_position(Position(GetScreenWidth() / 2, GetScreenHeight() / 2));
			ball.change_speed(BALL_SPEED_X, BALL_SPEED_Y);
			ball.reset_acceleration();
		}
	}
	void loop() {
		while (!WindowShouldClose()) {
			gameplay();
			render();
		}
	}
	void render() {
		BeginDrawing();

			ClearBackground(BLACK);

			player_one.render();
			player_two.render();

			ball.render();

		EndDrawing();
	}
	bool check_ball_paddle_collision(Ball b, Paddle p) {
		return CheckCollisionCircleRec(Vector2{ b.get_position().x, b.get_position().y }, BALL_RADIUS, p.get_rec());
	}
public:
	Game(u32 Width, u32 Height) {
		height = Height;
		width = Width;

		init_game();
	}
};