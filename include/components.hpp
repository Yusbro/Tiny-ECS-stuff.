#pragma once
#include <raylib.h>

//basic components!!!
struct Transform_Component
{
	Vector3 position;
	float scale=1;
	float rotation = 0;
};

struct Renderer_Component{
	int model_id;
};

struct Camera_Component
{
	Camera camera;
	float zoom;
};

struct Move_Component
{
	Vector3 target;	
};


//basic component tags!
struct Object_Renderer:Renderer_Component{};
struct TileMap_Renderer:Renderer_Component{};
struct Billboard_Renderer:Renderer_Component{};

//entity tags
struct PlayerTag{};
struct GroundTag{};
struct TitanTag{};
struct PeopleTag{};
