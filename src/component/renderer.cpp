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


void Renderer::tile_renderer(World &world, AssetData &asset_data)
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
	std::vector<int> tilemap_arch = world.Get_Archtype<Transform_Component, TileMap_Renderer, GroundTag>();
	
	for(int j : tilemap_arch)
	{
		std::vector<Transform_Component>* transform_arr = world.Fetch_Data<Transform_Component>(j);	
		std::vector<TileMap_Renderer>* tilemap_arr = world.Fetch_Data<TileMap_Renderer>(j);
		
		int tx = cam_to_world.x/(TINY_BORDER_SIZE*TILE_SIZE);
		int ty = cam_to_world.z/(TINY_BORDER_SIZE*TILE_SIZE);
		
		
		auto draw_tile = [&](int x, int y){
			int index = (x + y * (BORDER_SIZE/TINY_BORDER_SIZE)) * TINY_BORDER_AREA;
			if(index <0 || index+TINY_BORDER_AREA > (BORDER_SIZE*BORDER_SIZE))	return;
			for(int i=index; i < index + TINY_BORDER_AREA; i++){
				
				Transform_Component transform = (*transform_arr)[i];
				TileMap_Renderer tilemap = (*tilemap_arr)[i];

				Vector3 pos = transform.position;
				int model_id = tilemap.model_id;
		
				DrawModel(asset_data.Models[model_id], pos, TILE_SIZE, WHITE);		
			}
		};

		draw_tile(tx, ty);	
		draw_tile(tx+1, ty);	
		draw_tile(tx-1, ty);
		draw_tile(tx, ty+1);
		draw_tile(tx, ty-1);
		draw_tile(tx+1, ty+1);
		draw_tile(tx-1, ty-1);
		draw_tile(tx+1, ty-1);
		draw_tile(tx-1, ty+1);
	}
}



void Renderer::ui_renderer(World &world, AssetData &asset_data)
{
	std::vector<int> arch = world.Get_Archtype<Transform_Component, UI_Renderer>();	
	
	for(int arch_id:arch){
		std::vector<Transform_Component>* transform_arr = world.Fetch_Data<Transform_Component>(arch_id);
		std::vector<UI_Renderer>* ui_arr = world.Fetch_Data<UI_Renderer>(arch_id);

		for(int i=0;i<transform_arr->size(); i++){
			Vector3 position = (*transform_arr)[i].position;
			int texture_id = (*ui_arr)[i].model_id;
			DrawTexture(asset_data.Billboard[texture_id], position.x, position.y, WHITE);
		}
	}

}
