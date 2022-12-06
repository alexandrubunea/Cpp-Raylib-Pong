#include <string>
#include "raylib.h"
#include "Utils.cpp"
#include "Paddle.cpp"
#include "Ball.cpp"

const float	PADDLE_WIDTH = 20.0;
const float	PADDLE_HEIGHT = 100.0;
const float	PADDLE_SPEED = 600.0;
const Color	PADDLE_COLOR = WHITE;

const float	BALL_RADIUS	= 5.0;
const float BALL_SPEED_X = 300.0;
const float BALL_SPEED_Y = 300.0;
const float BALL_ACCELERATION = 1.1;
const Color	BALL_COLOR = WHITE;

const s32 SCORE_TEXT_SIZE = 30;
const Color TEXT_COLOR = WHITE;

class Game {
private:
	u32 height, width;
	Paddle player_one, player_two;
	Ball ball;
	u32 player_one_score = 0, player_two_score = 0;

	void init_game() {
		InitWindow(width, height, "Pong");
		SetWindowState(FLAG_VSYNC_HINT);

		Position player_one_position, player_two_position;

		player_one_position = Position(PADDLE_WIDTH * 2, GetScreenHeight() / 2);
		player_two_position = Position(GetScreenWidth() - PADDLE_WIDTH * 2, GetScreenHeight() / 2);

		player_one = Paddle(player_one_position, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED, PADDLE_COLOR);
		player_two = Paddle(player_two_position, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED, PADDLE_COLOR);

		Position ball_position = Position(GetScreenWidth() / 2, GetScreenHeight() / 2);

		ball = Ball(ball_position, BALL_RADIUS, BALL_SPEED_X, BALL_SPEED_Y, BALL_COLOR);

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
			ball.change_speed_x(ball.get_speed_x() * -BALL_ACCELERATION);

			float distance = player_one.get_position().x - ball.get_position().x;
			float ratio = distance / (PADDLE_WIDTH / 2);
			float bounceAngle = ratio * ball.get_speed_x();

			ball.change_speed_y(bounceAngle);
		}
		if (check_ball_paddle_collision(ball, player_two) && ball.get_speed_x() > 0) {
			ball.change_speed_x(ball.get_speed_x() * -BALL_ACCELERATION);

			float distance = player_two.get_position().x - ball.get_position().x;
			float ratio = distance / (PADDLE_WIDTH / 2);
			float bounceAngle = ratio * -ball.get_speed_x();

			ball.change_speed_y(bounceAngle);
		}

		/*
			Check if it was a score
		*/
		if (ball.get_position().x - BALL_RADIUS <= 0) {
			ball.change_position(Position(GetScreenWidth() / 2, GetScreenHeight() / 2));
			ball.change_speed_x(-BALL_SPEED_X);
			ball.change_speed_y(BALL_SPEED_Y);
			player_two_score++;
		}
		if (ball.get_position().x + BALL_RADIUS >= GetScreenWidth()) {
			ball.change_position(Position(GetScreenWidth() / 2, GetScreenHeight() / 2));
			ball.change_speed_x(BALL_SPEED_X);
			ball.change_speed_y(BALL_SPEED_Y);
			player_one_score++;
		}

		/*
			Exit key
		*/
		if (IsKeyPressed(KEY_ESCAPE)) {
			CloseWindow();
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

			/*
				Score
			*/
			std::string score;
			score = std::to_string(player_one_score) + ":" + std::to_string(player_two_score);
			DrawText(score.c_str(), GetScreenWidth() / 2 - MeasureText(score.c_str(), SCORE_TEXT_SIZE) / 2, 30, SCORE_TEXT_SIZE, TEXT_COLOR);

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