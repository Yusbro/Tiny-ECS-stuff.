
#include "../../include/components.hpp"
#include "../../include/component/kinematic.hpp"
#include <raymath.h>

void Kinematic::Move_Towards(World &world)
{
	std::vector<int> move_arch = world.Get_Archtype<Transform_Component, Move_Component>();
	
	for(int arch_index : move_arch)
	{
		
		std::vector<Transform_Component>* transform_arr = world.Fetch_Data<Transform_Component>(arch_index);
		std::vector<Move_Component>* move_arr = world.Fetch_Data<Move_Component>(arch_index);

		for(int i=0; i<transform_arr->size(); i++)
		{
			Move_Component _move = (*move_arr)[i];
			
			Transform_Component _transform = (*transform_arr)[i];
		
			Vector3 direction = Vector3Subtract(_transform.position, _move.target);
			direction = Vector3Normalize(direction);
			direction = Vector3Multiply(direction, {0.5,0,0.5});

			(*transform_arr)[i].position = Vector3Add(_transform.position, direction); 
		}
	}
	
}
