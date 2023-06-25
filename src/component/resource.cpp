#include "../../include/component/resource.hpp"
#include "../../include/components.hpp"
#include <raylib.h>
#include <iostream>


void Resource::Update_Resource(World &world)
{
	std::vector<int> arch = world.Get_Archtype<ResourceCounter_Component>();	
	for(int i:arch)
	{
		std::vector<ResourceCounter_Component>* resource_arr = world.Fetch_Data<ResourceCounter_Component>(i);
		for(int j=0;j<resource_arr->size(); j++)
		{
			if( (*resource_arr)[j].timer > 0){
				(*resource_arr)[j].timer -= 0.1;
				continue;
			}
			(*resource_arr)[j].timer = (float)GetRandomValue(1,5);
			int r = (*resource_arr)[j].Resource;
			(*resource_arr)[j].Actual_Resource += r;	
		}
	}
}
