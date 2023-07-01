#include "../../include/component/button.hpp"
#include "../../include/components.hpp"

#include <raylib.h>

void Button::button_poll(World &world)
{
	int is_mouse_pressed = 0;
	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
		is_mouse_pressed = 1;
	}
	Vector2 mouse_pos = GetMousePosition();

	std::vector<int> arch = world.Get_Archtype<Transform_Component, Button_Component, Box_Collider>();
	
	for(int id:arch)
	{
		std::vector<Transform_Component>* transform_arr = world.Fetch_Data<Transform_Component>(id);	
		std::vector<Button_Component>* button_arr = world.Fetch_Data<Button_Component>(id);	
		std::vector<Box_Collider>* box_collider_arr = world.Fetch_Data<Box_Collider>(id);
		
		for(int i=0; i<transform_arr->size(); i++)
		{
			Vector3 position = (*transform_arr)[i].position;
			Box_Collider collider = (*box_collider_arr)[i];

			if(mouse_pos.x > position.x && mouse_pos.y > position.y && mouse_pos.x < position.x+collider.w && mouse_pos.y < position.y+collider.h)
			{
				(*button_arr)[i].is_pressed = is_mouse_pressed;
			}
			else{
				(*button_arr)[i].is_pressed = 0;
			}
		}


	}	
}
