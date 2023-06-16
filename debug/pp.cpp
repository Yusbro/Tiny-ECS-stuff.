#include <raylib.h>


int main(){

	InitWindow(800, 600, "CRAP");
	Model model = LoadModel("../asset/models/ground.obj");


	while(!WindowShouldClose()){


	}

	UnloadModel(model);
	CloseWindow();
	return 0;
}
