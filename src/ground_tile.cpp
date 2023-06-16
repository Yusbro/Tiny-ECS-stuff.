#include "../include/ground_tile.hpp"
#include "../include/components.hpp"
#include <raylib.h>
#include <raymath.h>

void GroundTile::init(World& world){
	int ground_tile = world.Add_Archtype<Position, Render, GroundTag>();

	int max_border_size = 100;
	for(int i=0;i<max_border_size * max_border_size;i++){
		int y = i/max_border_size;
		int x = i - (y * max_border_size);
		
		Position position = 
		{
			(float)x * 10,
			0,
			(float)y * 10
		};

		Render render = GetRandomValue(0, 1);
		GroundTag tag;

		world.Add_Entity(ground_tile, position, render, tag);
	}
}


void GroundTile::draw(World& world, AssetData& asset_data, Vector3 camera_center){
	std::vector<int> ground_tile_arch = world.Get_Archtype<Position, Render, GroundTag>();
	
	std::vector<Position>* position = world.Fetch_Data<Position>(ground_tile_arch[0]);
	std::vector<Render>* render = world.Fetch_Data<Render>(ground_tile_arch[0]);
	

	for(int i=0; i < position->size(); i++){	
		Position pos = (*position)[i];
		Render model_id = (*render)[i];
		
		float distance = Vector3Distance(camera_center, pos);

		if(distance<60){
			DrawModel(asset_data.Models[model_id], pos, 10, RED);	
		}	
	}
}
