#include <raylib.h>
#include "../include/app.hpp"
int main()
{

	
	InitWindow(800, 600, "Happy bday yuuu boo!!");
	SetTargetFPS(60);


	Game game = Game();
	game.init();

		
	while (!WindowShouldClose())
	{
		game.update();
		game.draw();
	}
	game.deinit();
	CloseWindow();
	return 0;
}
