#include "ecs.hpp"
#include "asset_data.hpp"
#include "components.hpp"
#include <raylib.h>

#define MAX_ENEMY 10000
namespace Titan
{
	void init(World &world);
	void update(World &world);
	void draw(World &world, AssetData &asset_data, Vector3 camera_center);

	//some private functions!
	inline void move(std::vector<Transform_Component>* transform, std::vector<Move_Component>* move);
};
