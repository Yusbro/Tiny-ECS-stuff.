#include "config.hpp"
#include "components.hpp"
#include "ecs.hpp"

namespace Player{
	void init(World &world);
	void update(World &world);
	void draw(World &world);

	inline void player_move(Transform_Component& position, Camera_Component& camera);
	inline void tile_change(
			std::vector<TileMap_Renderer>* render,
			Camera_Component camera,
			std::vector<ResourceCounter_Component>* resource_arr
			);

	Vector3 camera_center(Camera camera);
};
