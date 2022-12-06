#include "raylib.h"
#include "Utils.cpp"
#include "Paddle.cpp"
#include "Ball.cpp"

const float		PADDLE_WIDTH		= 20.0;
const float		PADDLE_HEIGHT		= 100.0;
const float		PADDLE_ACCELERATION = .3;
const Color		PADDLE_COLOR		= WHITE;

const float		BALL_RADIUS			= 5.0;
const Color		BALL_COLOR			= WHITE;

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

		player_one = Paddle(player_one_position, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_ACCELERATION, PADDLE_COLOR);
		player_two = Paddle(player_two_position, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_ACCELERATION, PADDLE_COLOR);

		Position ball_position = Position(GetScreenWidth() / 2, GetScreenHeight() / 2);

		ball = Ball(ball_position, BALL_RADIUS, BALL_COLOR);

		loop();
	}
	void loop() {
		while (!WindowShouldClose()) {

			player_one.controller(KEY_W, KEY_S);
			player_two.controller(KEY_UP, KEY_DOWN);
			
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
public:
	Game(u32 Width, u32 Height) {
		height = Height;
		width = Width;

		init_game();
	}
};