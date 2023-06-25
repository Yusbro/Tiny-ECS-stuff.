#include "../include/resource_counter.hpp"
#include <raymath.h>

void ResourceCounter::init(World &world)
{
	int arch = world.Add_Archtype<ResourceCounter_Component>();
	
	for(int i=0;i<10;i++)
	{
		ResourceCounter_Component resource_counter = { .timer = (float)GetRandomValue(1,5), .Resource = 0, .Actual_Resource = 0};
		world.Add_Entity(arch, resource_counter);
	}
}
