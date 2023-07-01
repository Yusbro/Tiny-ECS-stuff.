#pragma once
#include <raylib.h>
#include <vector>
#include <array>

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

struct ResourceCounter_Component
{
	float timer;
	int Resource;
	int Actual_Resource;
};

struct Collider_Component{};

struct Box_Collider:Collider_Component{
	int w,h;	
};

struct Button_Component{
	int is_pressed=0;
};


//basic component tags!
struct Object_Renderer:Renderer_Component{};
struct TileMap_Renderer:Renderer_Component{};
struct Billboard_Renderer:Renderer_Component{};
struct UI_Renderer:Renderer_Component{
	int layer=0;
};

//entity tags
struct PlayerTag{};
struct GroundTag{};
struct TitanTag{};
struct PeopleTag{};
struct GameUiTag{};
