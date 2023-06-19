#include "../include/titan.hpp"
#include "../include/components.hpp"

#include <raylib.h>
#include <raymath.h>

void Titan::init(World &world)
{
	int titan_arch = world.Add_Archtype<Transform_Component, Renderer_Component, Move_Component, TitanTag>();
	
	for(int i=0;i<100; i++)
	{
		Transform_Component position = {
			.position={
				(float)GetRandomValue(0, 1000),
				5,
				(float)GetRandomValue(0, 1000)
			},
			.rotation = 0
		};
		Renderer_Component render = {
			.model_id = 2
		};

		Move_Component move = {
			.target = {
				(float)GetRandomValue(0, 1000),
				5,
				(float)GetRandomValue(0, 1000)	
			}
		};
		TitanTag tag;

		world.Add_Entity(titan_arch, position, render,move, tag);
	}
}

void Titan::update(World &world)
{
	std::vector<int> titan_arch = world.Get_Archtype<Transform_Component, Move_Component, TitanTag>();

	std::vector<Transform_Component>* position = world.Fetch_Data<Transform_Component>(titan_arch[0]);
	std::vector<Move_Component>* move = world.Fetch_Data<Move_Component>(titan_arch[0]);	
	
	
	Titan::move(position, move);
}

void Titan::draw(World &world,AssetData &asset_data, Vector3 camera_center)
{
	std::vector<int> titan_arch = world.Get_Archtype<Transform_Component, Renderer_Component, TitanTag>();

	std::vector<Transform_Component>* position = world.Fetch_Data<Transform_Component>(titan_arch[0]);
	std::vector<Renderer_Component>* render = world.Fetch_Data<Renderer_Component>(titan_arch[0]);
	
	for(int i=0; i< position->size(); i++)
	{	
		float rotation = (*position)[i].rotation;
		Vector3 pos = (*position)[i].position;
		int model_id = (*render)[i].model_id;
		
		float distance = Vector3Distance(pos, camera_center);
		if(distance < 70){
			DrawModelEx(asset_data.Models[model_id], pos, {0, 1, 0}, rotation, {0.3, 0.3, 0.3}, WHITE); 
		}
	}	
}


inline void Titan::move(std::vector<Transform_Component>* transform, std::vector<Move_Component>* move)
{
	for(int i=0; i<transform->size(); i++)
	{
		Move_Component _move = (*move)[i];
		Transform_Component _transform = (*transform)[i];
		
		Vector3 direction = Vector3Subtract(_transform.position, _move.target);
		direction = Vector3Normalize(direction);
		direction = Vector3Multiply(direction, {0.5,0,0.5});

		(*transform)[i].position = Vector3Add(_transform.position, direction); 
	}	
}

