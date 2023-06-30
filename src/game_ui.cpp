#include "../include/game_ui.hpp"
#include "../include/components.hpp"

void GameUI::init(World &world)
{
	int ui_elements = world.Add_Archtype<Transform_Component,UI_Renderer>();

	//adding a tiny button
	Transform_Component position = {
		.position = {50, 50, 0},
		.scale = 30.0
	};

	UI_Renderer ui;
	ui.model_id = 0;
	
	world.Add_Entity(ui_elements, position, ui);
}

void GameUI::update(World &world)
{


}
