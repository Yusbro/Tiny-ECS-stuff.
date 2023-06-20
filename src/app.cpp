#include "../include/app.hpp"
#include "../include/json.hpp"
#include "../include/components.hpp"
#include "../include/component/renderer.hpp"

//the entity stuff
#include "../include/player.hpp"
#include "../include/ground_tile.hpp"
#include "../include/titan.hpp"

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
	
	
	asset_data.shader = LoadShader("", "asset/shader/world.fs");

	if(data.contains("models") && data["models"].is_object()){
		for(auto i = data["models"].begin(); i != data["models"].end(); i++ ){
			std::string k = i.key();
			std::cout<<"[ASSET LOAD] loaded "<<k<<std::endl;
			const json value = i.value();//the path array!!!
			
			std::string model_path = value[0];
			std::string texture_path = value[1];//"asset/models/ground_tex.png";

			Model model = LoadModel(model_path.c_str());
			Texture2D texture = LoadTexture(texture_path.c_str());
			
			model.materials[0].shader = asset_data.shader;
			model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

			Game::asset_data.Models.push_back(model);
		}
		std::cout<<"done loading the models"<<std::endl;
	}

	//loading all the entity and stuff!!!
	Player::init(Game::world);
	GroundTile::init(Game::world);
	Titan::init(Game::world);
	
	Game::render_texture = LoadRenderTexture(400, 300);
	std::cout<<"Done with init stuff"<<std::endl;
}


void Game::update(){
	Player::update(Game::world);
	Titan::update(Game::world);
}

void Game::draw(){
	//drawing every stuff to a render texture
	BeginTextureMode(Game::render_texture);//BeginDrawing();
		ClearBackground(WHITE);
		
		std::vector<int> camera_arch = Game::world.Get_Archtype<Camera_Component>();
		std::vector<Camera_Component> camera = *Game::world.Fetch_Data<Camera_Component>(camera_arch[0]);
		
		Vector3 _camera_center = Game::camera_center(camera[0].camera);
		BeginMode3D(camera[0].camera);
			GroundTile::draw(Game::world, Game::asset_data, _camera_center);
			Player::draw(Game::world);

			Renderer::model_renderer(Game::world, Game::asset_data);

		EndMode3D();
	EndTextureMode();

	BeginDrawing();	
		DrawTexturePro(Game::render_texture.texture, (Rectangle){0,0, 400, -300}, (Rectangle){0,0, 1024, 800}, {0,0}, 0, WHITE);
		DrawFPS(50, 50);
	EndDrawing();
}

void Game::deinit(){
	UnloadShader(Game::asset_data.shader);
	Game::asset_data.unload_models();
	UnloadRenderTexture(Game::render_texture);
}


Game::Game(){}
Game::~Game(){}


//private functions!
Vector3 Game::camera_center(Camera camera){
	Vector3 ret;
		
	Ray ray = GetMouseRay({512, 400}, camera);
	Vector3 a = {-5000.0, 0.0, -5000.0};
	Vector3 b = {-5000.0, 0.0, 5000.0};
	Vector3 c = {5000.0, 0.0, 5000.0};
	Vector3 d = {5000.0, 0.0, -5000.0};
	
	RayCollision groundHitInfo = GetRayCollisionQuad(ray, a, b, c, d);
	if(groundHitInfo.hit){
		ret = groundHitInfo.point;
	}

	return ret;
}






