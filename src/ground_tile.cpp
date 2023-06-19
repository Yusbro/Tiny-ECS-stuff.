#include "../include/ground_tile.hpp"
#include "../include/components.hpp"
#include <raylib.h>
#include <raymath.h>

void GroundTile::init(World& world){
	int ground_tile = world.Add_Archtype<Transform_Component, Renderer_Component, GroundTag>();

	int max_border_size = BORDER_SIZE;
	for(int i=0;i<max_border_size * max_border_size;i++){
		int y = i/max_border_size;
		int x = i - (y * max_border_size);
		
		Transform_Component position = 
		{
			.position{
				(float)x * 10,
				0,
				(float)y * 10
			}
		};

		Renderer_Component render = {.model_id=0};//GetRandomValue(0, 1);
		GroundTag tag;

		world.Add_Entity(ground_tile, position, render, tag);
	}
}

void GroundTile::draw(World& world, AssetData& asset_data, Vector3 camera_center){
	std::vector<int> ground_tile_arch = world.Get_Archtype<Transform_Component, Renderer_Component, GroundTag>();
	
	std::vector<Transform_Component>* position = world.Fetch_Data<Transform_Component>(ground_tile_arch[0]);
	std::vector<Renderer_Component>* render = world.Fetch_Data<Renderer_Component>(ground_tile_arch[0]);
	

	for(int i=0; i < position->size(); i++){	
		Vector3 pos = (*position)[i].position;
		int model_id = (*render)[i].model_id;
		
		float distance = Vector3Distance(camera_center, pos);

		if(distance<70){
			DrawModel(asset_data.Models[model_id], pos, TILE_SIZE, WHITE);	
		}	
	}
}


