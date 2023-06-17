#include "ecs.hpp"
#include "../include/asset_data.hpp"

#define TILE_SIZE 10
#define BORDER_SIZE 100

namespace GroundTile{
	void init(World& world);
	void deinit(World &world);
	void draw(World& world, AssetData& asset_data, Vector3 camera_center);	
};
