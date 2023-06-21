#include "ecs.hpp"
#include "asset_data.hpp"
#include "components.hpp"
#include "config.hpp"

#include <raylib.h>

#define MAX_ENEMY 10000
namespace Titan
{
	void init(World &world);
	void update(World &world);

	//private stuff
	inline void move_dir(
			std::vector<Transform_Component>* position,
			std::vector<Move_Component>* move,
			std::vector<Transform_Component>* tile_transform,
			std::vector<TileMap_Renderer>* tile_render
			);
};
