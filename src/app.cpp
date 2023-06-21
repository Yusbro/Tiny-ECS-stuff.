#include "../include/app.hpp"
#include "../include/json.hpp"
#include "../include/components.hpp"
#include "../include/asset_load.hpp"

//all the component stuff
#include "../include/component/kinematic.hpp"
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
	Asset_Loader::load_shader(Game::asset_data);
	Asset_Loader::load_models(Game::asset_data);
	Asset_Loader::load_billboard(Game::asset_data);

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
	

	//core component update!!!
	Kinematic::Move_Towards(Game::world);
}

void Game::draw(){
	//drawing every stuff to a render texture
	BeginTextureMode(Game::render_texture);//BeginDrawing();
		ClearBackground(WHITE);
		
		std::vector<int> camera_arch = Game::world.Get_Archtype<Camera_Component>();
		std::vector<Camera_Component> camera = *Game::world.Fetch_Data<Camera_Component>(camera_arch[0]);
		
		Vector3 _camera_center = Game::camera_center(camera[0].camera);
		BeginMode3D(camera[0].camera);
			Player::draw(Game::world);

			Renderer::model_renderer(Game::world, Game::asset_data);
			Renderer::tile_renderer(Game::world, Game::asset_data);

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
	Game::asset_data.unload_billboard();
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






