#include "../include/game_ui.hpp"
#include "../include/components.hpp"

void GameUI::init(World &world)
{
	int ui_elements = world.Add_Archtype<
		Transform_Component,
		UI_Renderer,
		Button_Component,
		Box_Collider,
		GameUiTag
		>();

	//adding a tiny button
	Transform_Component position = {
		.position = {50, 50, 0},
		.scale = 3.0
	};

	UI_Renderer ui;
	ui.model_id = 0;

	Button_Component button;
	
	Box_Collider box_collider;
	box_collider.w = 64*3;
	box_collider.h = 64*3;

	GameUiTag tag;
	
	world.Add_Entity(ui_elements, position, ui, button, box_collider, tag);
}

void GameUI::update(World &world)
{
	std::vector<int> arch = world.Get_Archtype<Button_Component, GameUiTag>();
	
	for(int i:arch){
		std::vector<Button_Component>* button_arr = world.Fetch_Data<Button_Component>(arch[i]);
	
		if((*button_arr)[0].is_pressed == 1)
		{
			std::cout<<"YUSHH!!![GAME_UI]"<<std::endl;
		}
	}
}
