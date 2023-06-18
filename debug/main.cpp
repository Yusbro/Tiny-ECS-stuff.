#include "vecs.hpp"
#include <iostream>


struct Position{
	float x,y;
};

struct Color{
	float x,y,z;
};

struct Size{
	float x;
};

int main(){
	World world;

	int p = world.Add_Archtype<Position>();
	int pc = world.Add_Archtype<Position, Color>();
	int pcs = world.Add_Archtype<Position, Color, Size>();

	float position_counter = 0;
	float color_counter = 0;
	float size_counter = 0;

	for(int i=0;i<10;i++){
		world.Add_Entity(p, (Position){position_counter, position_counter});
		position_counter += 1;
	}
	
	
	for(int i=0;i<10;i++){
		world.Add_Entity(pc, (Position){position_counter, position_counter}, (Color){color_counter, color_counter});
		position_counter += 1;
		color_counter += 1;
	}
		
	for(int i=0;i<10;i++){
		world.Add_Entity(pcs, (Position){position_counter, position_counter}, (Color){color_counter, color_counter}, (Size){size_counter});
		position_counter += 1;
		color_counter += 1;
		size_counter += 1;
	}
	
	//accessing da value!!
	std::vector<int> position = world.Get_Archtype<Position>();
	
	for(int i : position){
		std::vector<Position>* data = world.Fetch_Data<Position>(i);
		for(Position p : (*data)){
			std::cout<<p.x<<std::endl;
		}
	}

	return 0;
}
