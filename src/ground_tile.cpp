#include "../include/ground_tile.hpp"
#include "../include/components.hpp"
#include <raylib.h>
#include <raymath.h>

void GroundTile::init(World& world){
	int ground_tile = world.Add_Archtype<
		Transform_Component,
		TileMap_Renderer,
		GroundTag>();
	
	int tiny_box_size = TINY_BORDER_SIZE;
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
				(float)xx * TILE_SIZE,
				0,
				(float)yy * TILE_SIZE
			}
		};

		//Renderer_Component render = {.model_id=0};//GetRandomValue(0, 1);
		TileMap_Renderer render;
		render.model_id = 0;

		GroundTag tag;

		world.Add_Entity(ground_tile, position, render, tag);
	}
}


