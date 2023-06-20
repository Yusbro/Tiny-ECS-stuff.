#include "../include/titan.hpp"
#include "../include/components.hpp"

#include <raylib.h>
#include <raymath.h>

void Titan::init(World &world)
{
	int titan_arch = world.Add_Archtype<
		Transform_Component,
		Object_Renderer,
		Move_Component,
		TitanTag
		>();
	
	for(int i=0;i<100; i++)
	{
		Transform_Component position = {
			.position={
				(float)GetRandomValue(0, 100),
				5,
				(float)GetRandomValue(0, 100)
			},
			.scale = 0.3,
			.rotation = 0
		};
		Object_Renderer render;
		render.model_id = 2;

		Move_Component move = {
			.target = {
				0,
				0,
				0	
			}
		};
		TitanTag tag;

		world.Add_Entity(titan_arch, position, render,move, tag);
	}
}

void Titan::update(World &world)
{
	std::vector<int> titan_arch = world.Get_Archtype<Transform_Component, Move_Component, TitanTag>();
	std::vector<int> tilemap_arch = world.Get_Archtype<Transform_Component, TileMap_Renderer>();

	std::vector<Transform_Component>* position = world.Fetch_Data<Transform_Component>(titan_arch[0]);
	std::vector<Move_Component>* move = world.Fetch_Data<Move_Component>(titan_arch[0]);

	std::vector<Transform_Component>* tile_transform_arch = world.Fetch_Data<Transform_Component>(tilemap_arch[0]);		
	std::vector<TileMap_Renderer>* tile_render_arch = world.Fetch_Data<TileMap_Renderer>(tilemap_arch[0]);	
	
	
}


void Titan::move_dir(
		std::vector<Transform_Component>* transform_arr,
		std::vector<Move_Component>* move_arr,
		std::vector<Transform_Component>* tile_transform_arr,
		std::vector<TileMap_Renderer>* tile_render_arr
		)
{


	for(int i=0; i<transform_arr->size(); i++)
	{
		if(Vector3Length((*move_arr)[i].target) <= 2) continue;
			

	}
}
