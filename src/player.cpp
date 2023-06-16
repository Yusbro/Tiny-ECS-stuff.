#include "../include/player.hpp"
#include "../include/components.hpp"

void Player::init(World& world)
{	
	Position position = {10,10,10};

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
	std::vector<int> player = world.Get_Archtype<Position, Camera, PlayerTag>();
	
	std::vector<Position> position = *world.Fetch_Data<Position>(player[0]);
	std::vector<Camera> camera = *world.Fetch_Data<Camera>(player[0]);
	
	Player::player_move(position[0], camera[0]);
}

//private functions!!!
inline void Player::player_move(Position& position, Camera& camera){
	//getting da controls!
	int x=0, y=0;
	if(IsKeyDown(KEY_W)) y = 1;
	if(IsKeyDown(KEY_A)) x = -1;
	if(IsKeyDown(KEY_S)) y = -1;
	if(IsKeyDown(KEY_D)) x = 1;

	position.x += x;
	position.z += y;

	camera.position = position;
	camera.target = {position.x - 10, position.y - 10, position.z - 10};
}
