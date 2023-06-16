#include "../include/app.hpp"
#include "../include/json.hpp"
#include "../include/components.hpp"

//the entity stuff
#include "../include/player.hpp"
#include "../include/ground_tile.hpp"

#include <raylib.h>
#include <fstream>
#include <string>
#include <iostream>
#include <map>



using json = nlohmann::json;

void Game::init(){

	//loading all the assets!!!
	std::ifstream f("asset/asset.json");
	std::string fileContent({std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>()});
	
	std::cout<<fileContent<<std::endl;

	json data = json::parse(fileContent);
	std::cout<<"asset json parased!"<<std::endl;
	
	if(data.contains("models") && data["models"].is_object()){
		for(auto i = data["models"].begin(); i != data["models"].end(); ++i ){
			std::string k = i.key();
			const json value = i.value();//the path array!!!
			
			std::string model_path = value[0];
			std::string texture_path = value[1];//"asset/models/ground_tex.png";

			Model model = LoadModel(model_path.c_str());
			model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTexture(texture_path.c_str());

			Game::asset_data.Models.push_back(model);
		}
		std::cout<<"done loading the models"<<std::endl;
	}


	//loading all the entity and stuff!!!
	Player::init(Game::world);
	GroundTile::init(Game::world);

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
		
		Vector3 _camera_center = Game::camera_center(camera[0]);
		BeginMode3D(camera[0]);
			DrawGrid(10, 5);
			DrawCube({0,0,0}, 1, 1, 1, RED);
			GroundTile::draw(Game::world, Game::asset_data, _camera_center);
		EndMode3D();

	EndDrawing();
}

void Game::deinit(){
	Game::asset_data.unload_models();
}




Game::Game(){}
Game::~Game(){}




//private functions!
Vector3 Game::camera_center(Camera camera){
	Vector3 ret;
		
	Ray ray = GetMouseRay({400, 300}, camera);
	Vector3 a = {-500.0, 0.0, -500.0};
	Vector3 b = {-500.0, 0.0, 500.0};
	Vector3 c = {500.0, 0.0, 500.0};
	Vector3 d = {500.0, 0.0, -500.0};
	
	RayCollision groundHitInfo = GetRayCollisionQuad(ray, a, b, c, d);
	if(groundHitInfo.hit){
		ret = groundHitInfo.point;
	}

	return ret;
}






