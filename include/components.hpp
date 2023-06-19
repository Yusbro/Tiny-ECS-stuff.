#pragma once
#include <raylib.h>

//basic components!!!
struct Transform_Component
{
	Vector3 position;
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


struct PlayerTag{};

struct GroundTag{};

struct TitanTag{};
