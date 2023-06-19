#include "../include/player.hpp"
#include "../include/components.hpp"

#include <raymath.h>
#include <iostream>

void Player::init(World& world)
{	
	Transform_Component transform_component = {.position={50,50,50}};

	Camera camera;
	camera.position = transform_component.position;
	camera.target = {0,0,0};
	camera.projection = CAMERA_ORTHOGRAPHIC;
	camera.up = {0, 1, 0};
	camera.fovy = 60.0f;
	
	Camera_Component camera_component = {.camera{camera}};

	PlayerTag tag;
	
	int player = world.Add_Archtype<Transform_Component, Camera_Component, PlayerTag>();
	world.Add_Entity<Transform_Component, Camera_Component, PlayerTag>(player, transform_component, camera_component, tag);
}

void Player::update(World& world)
{	
	//getting the player's archtype
	std::vector<int> player = world.Get_Archtype<Transform_Component, Camera_Component, PlayerTag>();
	std::vector<int> ground_tile_arch = world.Get_Archtype<Renderer_Component, GroundTag>();

	//getting the player's position and camera component!
	std::vector<Transform_Component>* position = world.Fetch_Data<Transform_Component>(player[0]);
	std::vector<Camera_Component>* camera = world.Fetch_Data<Camera_Component>(player[0]);	
	std::vector<Renderer_Component>* ground_tile_render = world.Fetch_Data<Renderer_Component>(ground_tile_arch[0]);


	//making the player move
	Player::player_move((*position)[0], (*camera)[0]);
	

	//---for the tile stuff!!
	Player::tile_change(ground_tile_render, (*camera)[0]);
}


void Player::draw(World &world)
{
	//getting the player archtype
	std::vector<int> player = world.Get_Archtype<Transform_Component, Camera_Component, PlayerTag>();
	
	//getting da camera component!!
	std::vector<Camera_Component>* camera = world.Fetch_Data<Camera_Component>(player[0]);
	
	//getting da cursor to world position
	Vector3 mouse_to_world = Player::camera_center((*camera)[0].camera);
	
	//
	mouse_to_world.x += 10 * 0.5;
	mouse_to_world.z += 10 * 0.5;

	mouse_to_world.x = floor(mouse_to_world.x / 10) * 10;	
	mouse_to_world.z = floor(mouse_to_world.z / 10) * 10;	
	
	DrawCube(mouse_to_world, 3, 3, 3, RED);
}


inline void Player::tile_change(std::vector<Renderer_Component>* render, Camera_Component camera){	
	Vector3 mouse_to_world = Player::camera_center(camera.camera);
	
	//converting mouse position to indexed position!
	mouse_to_world.x += 10 * 0.5;
	mouse_to_world.z += 10 * 0.5;

	int x = mouse_to_world.x / 10;	
	int y = mouse_to_world.z / 10;

	int index = x + y * 100;
	if(IsMouseButtonPressed(0)){
		(*render)[index].model_id = 1;
	}	
}


//private functions!!!
inline void Player::player_move(Transform_Component& transform, Camera_Component& camera){
	//getting da controls!
	float x=0, y=0;
	if(IsKeyDown(KEY_W)) y = -1;
	if(IsKeyDown(KEY_A)) x = -1;
	if(IsKeyDown(KEY_S)) y = 1;
	if(IsKeyDown(KEY_D)) x = 1;
		
	
	float move_angle = std::atan2(x, y) + 0.7853;
	
	if(x!=0 || y!=0){
		transform.position.x += sin(move_angle) * 2;
		transform.position.z += cos(move_angle) * 2;
	}

	camera.camera.position = transform.position;
	camera.camera.target = {transform.position.x - 10, transform.position.y - 10, transform.position.z - 10};
}




Vector3 Player::camera_center(Camera camera){
	Vector3 ret;
	
	Vector2 mouse_position = GetMousePosition();

	Ray ray = GetMouseRay(mouse_position, camera);
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

