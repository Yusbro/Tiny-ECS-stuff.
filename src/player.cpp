#include "../include/player.hpp"
#include "../include/components.hpp"

#include <raymath.h>
#include <iostream>

void Player::init(World& world)
{	
	Position position = {50,50,50};

	Camera camera;
	camera.position = position;
	camera.target = {0,0,0};
	camera.projection = CAMERA_ORTHOGRAPHIC;
	camera.up = {0, 1, 0};
	camera.fovy = 60.0f;
	
	PlayerTag tag;
	
	int player = world.Add_Archtype<Position, Camera, PlayerTag>();
	world.Add_Entity<Position, Camera, PlayerTag>(player, position, camera, tag);
}


void Player::update(World& world)
{	
	//getting the player's archtype
	std::vector<int> player = world.Get_Archtype<Position, Camera, PlayerTag>();
	
	//getting the player's position and camera component!
	std::vector<Position>* position = world.Fetch_Data<Position>(player[0]);
	std::vector<Camera>* camera = world.Fetch_Data<Camera>(player[0]);
	
	//making the player move
	Player::player_move((*position)[0], (*camera)[0]);
}

//private functions!!!
inline void Player::player_move(Position& position, Camera& camera){
	//getting da controls!
	float x=0, y=0;
	if(IsKeyDown(KEY_W)) y = -1;
	if(IsKeyDown(KEY_A)) x = -1;
	if(IsKeyDown(KEY_S)) y = 1;
	if(IsKeyDown(KEY_D)) x = 1;
		
	
	float move_angle = std::atan2(x, y) + 0.7853;
	
	if((x+y)!=0){
		position.x += sin(move_angle) * 2;
		position.z += cos(move_angle) * 2;
	}

	camera.position = position;
	camera.target = {position.x - 10, position.y - 10, position.z - 10};
}
