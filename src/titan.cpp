#include "../include/titan.hpp"
#include "../include/components.hpp"

#include <raylib.h>
#include <raymath.h>

void Titan::init(World &world)
{
	int titan_arch = world.Add_Archtype<Position, Render, TitanTag>();
	
	for(int i=0;i<MAX_ENEMY; i++)
	{
		Position position = {(float)GetRandomValue(0, 1000), 3, (float)GetRandomValue(0, 1000)};
		Render render = 2;
		Health health = 100;
		Target target = { 500, 1, 500};
		TitanTag tag;

		world.Add_Entity<Position, Render, TitanTag>(titan_arch, position, render, tag);
	}
		
}

void Titan::update(World &world)
{

}

void Titan::draw(World &world,AssetData &asset_data, Vector3 camera_center)
{
	std::vector<int> titan_arch = world.Get_Archtype<Position, Render, TitanTag>();

	std::vector<Position>* position = world.Fetch_Data<Position>(titan_arch[0]);
	std::vector<Render>* render = world.Fetch_Data<Render>(titan_arch[0]);
	
	for(int i=0; i< position->size(); i++)
	{
		Position pos = (*position)[i];
		Render model_id = (*render)[i];
		
		float distance = Vector3Distance(pos, camera_center);
		if(distance < 70){
			DrawModel(asset_data.Models[model_id], pos, 0.1, WHITE);	
		}
	}	
}
