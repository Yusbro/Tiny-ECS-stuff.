#include "../include/app.hpp"
#include "../include/json.hpp"
#include "../include/components.hpp"

//the entity stuff
#include "../include/player.hpp"


#include <raylib.h>
#include <fstream>
#include <string>
#include <iostream>

using json = nlohmann::json;

void Game::init(){

	//loading all the assets!!!
	std::ifstream f("asset/asset.json");
	std::string fileContent({std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>()});

	json data = json::parse(fileContent);
	std::vector<std::string> asset_name;
	
	if(data.contains("models") && data["models"].is_array()){
		for(std::string i : data["models"]){
			asset_name.push_back(i);
		}
	}

	//loading all the models and stuff!!
	for(auto i:asset_name){
		std::string model_path = data[i];
		Model model = LoadModel(model_path.c_str());
		Game::asset_data.Models.push_back(model);
	}



	//loading all the entity and stuff!!!
	Player::init(Game::world);


	std::cout<<"Done with init stuff"<<std::endl;
}


void Game::update(){
	Player::update(Game::world);
}

void Game::draw(){
	BeginDrawing();
		ClearBackground(WHITE);
		DrawFPS(50, 50);


		std::vector<int> camera_arch = Game::world.Get_Archtype<Camera>();
		std::vector<Camera> camera = *Game::world.Fetch_Data<Camera>(camera_arch[0]);
		
		BeginMode3D(camera[0]);
			DrawGrid(10, 5);
			DrawCube({0,0,0}, 1, 1, 1, RED);
		EndMode3D();

	EndDrawing();
}

void Game::deinit(){
	Game::asset_data.unload_models();
}




Game::Game(){}

Game::~Game(){}
