#include <raylib.h>
#include <raymath.h>
#include "../../include/components.hpp"
#include "../../include/component/renderer.hpp"
#include "../../include/ecs.hpp"

void Renderer::model_renderer(World &world, AssetData &asset_data)
{	
	auto camera_center = 
		[](Camera camera){
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
		};
	

	//getting the camera stuff!!!
	std::vector<int> camera_arch = world.Get_Archtype<Camera_Component>();
	std::vector<Camera_Component>* camera_arr = world.Fetch_Data<Camera_Component>(camera_arch[0]);

	Vector3 cam_to_world = camera_center((*camera_arr)[0].camera);

	//getting the archtype for da object renderer stuff!!
	std::vector<int> object_render_arch = world.Get_Archtype<Transform_Component, Object_Renderer>();

	for(int i : object_render_arch)
	{
		std::vector<Transform_Component>* transform_arr = world.Fetch_Data<Transform_Component>(i);
		std::vector<Object_Renderer>* object_renderer_arr = world.Fetch_Data<Object_Renderer>(i);	
		
		for(int i=0;i<transform_arr->size();i++)
		{	
			Transform_Component transform_component = (*transform_arr)[i];

			Vector3 position = transform_component.position;
			int model_id = (*object_renderer_arr)[i].model_id;
			float rotation = transform_component.rotation;
			float scale = transform_component.scale;
			
			float distance_from_cam_to_world = Vector3Distance(cam_to_world, position);
			if(distance_from_cam_to_world > 70) continue;

			DrawModelEx(asset_data.Models[model_id], position, {0, 1, 0}, rotation, {scale,scale,scale}, WHITE);	
		}
	}	
}


void tile_renderer(World &world, AssetData &asset_data)
{	
	auto camera_center = 
		[](Camera camera){
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
		};	

	//getting the camera stuff!!!
	std::vector<int> camera_arch = world.Get_Archtype<Camera_Component>();
	std::vector<Camera_Component>* camera_arr = world.Fetch_Data<Camera_Component>(camera_arch[0]);

	Vector3 cam_to_world = camera_center((*camera_arr)[0].camera);	
	
	
	//da tile renderer archtypes!
	std::vector<int> tilemap_arch = world.Get_Archtype<Transform_Component, TileMap_Renderer>();
	
	
	for(int i : tilemap_arch)
	{
		std::vector<Transform_Component> transform_arr = *world.Fetch_Data<Transform_Component>(i);	
		std::vector<TileMap_Renderer> tilemap_arr = *world.Fetch_Data<TileMap_Renderer>(i);
		
	}
}
