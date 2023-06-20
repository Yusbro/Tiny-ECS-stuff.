#include "../include/ground_tile.hpp"
#include "../include/components.hpp"
#include <raylib.h>
#include <raymath.h>

void GroundTile::init(World& world){
	int ground_tile = world.Add_Archtype<Transform_Component, Renderer_Component, GroundTag>();
	
	int tiny_box_size = 10;
	int big_box_size = BORDER_SIZE / tiny_box_size;

	int tiny_box_area = tiny_box_size * tiny_box_size;

	int max_border_size = BORDER_SIZE;
	for(int i=0;i<max_border_size * max_border_size;i++){

		int big_box_index = i/(tiny_box_size * tiny_box_size);

		int by = (big_box_index/big_box_size) * tiny_box_size;	
		int bx = (big_box_index - (big_box_index/big_box_size) * big_box_size) * tiny_box_size;// 
		
		int yy = ((i%(tiny_box_area))/tiny_box_size) + by;
		int xx = (i - (i/tiny_box_size) * tiny_box_size) + bx;
		
	
		Transform_Component position = 
		{
			.position{
				(float)xx * 10,
				0,
				(float)yy * 10
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
		
	int tx = camera_center.x/100;
	int ty = camera_center.z/100;

	auto draw_tile = [&](int x, int y){
		int index = (x + y * (BORDER_SIZE/10)) * 100;	
		if(index <0)	return;
		for(int i=index; i < index + 100; i++){	
			Vector3 pos = (*position)[i].position;
			int model_id = (*render)[i].model_id;
		
			DrawModel(asset_data.Models[model_id], pos, TILE_SIZE, WHITE);		
		}
	};

	draw_tile(tx, ty);	
	draw_tile(tx+1, ty);	
	draw_tile(tx-1, ty);
	draw_tile(tx, ty+1);
	draw_tile(tx, ty-1);
	draw_tile(tx+1, ty+1);
	draw_tile(tx-1, ty-1);
	draw_tile(tx+1, ty-1);
	draw_tile(tx-1, ty+1);
}


