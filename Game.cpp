#include "raylib.h"
#include "Utils.cpp"
#include "Paddle.cpp"
#include "Ball.cpp"

#define		PADDLE_WIDTH	20
#define		PADDLE_HEIGHT	100
#define		PADDLE_COLOR	WHITE

#define		BALL_RADIUS		5.0
#define		BALL_COLOR		WHITE

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

		player_one = Paddle(player_one_position, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_COLOR);
		player_two = Paddle(player_two_position, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_COLOR);

		Position ball_position = Position(GetScreenWidth() / 2, GetScreenHeight() / 2);

		ball = Ball(ball_position, BALL_RADIUS, BALL_COLOR);

		loop();
	}
	void loop() {
		while (!WindowShouldClose()) {
			BeginDrawing();

				render();
			
			EndDrawing();
		}
	}
	void render() {
		ClearBackground(BLACK);

		player_one.render();
		player_two.render();

		ball.render();
	}
public:
	Game(u32 Width, u32 Height) {
		height = Height;
		width = Width;

		init_game();
	}
};