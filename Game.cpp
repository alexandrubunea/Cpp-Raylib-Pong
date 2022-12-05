#include "raylib.h"
#include "Utils.cpp"

class Game {
private:
	u32 height, width;
	void init_game() {
		InitWindow(width, height, "Pong");
		SetWindowState(FLAG_VSYNC_HINT);

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
	}
public:
	Game(u32 Width, u32 Height) {
		height = Height;
		width = Width;

		init_game();
	}
};