#include "components.hpp"
#include "ecs.hpp"

namespace Player{
	void init(World &world);
	void deinit(World &world);
	void update(World &world);
	void draw(World &world);

	inline void player_move(Position& position, Camera& camera);
	inline void tile_change(std::vector<Render>* render, Camera camera);

	Vector3 camera_center(Camera camera);
};
