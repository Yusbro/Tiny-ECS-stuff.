#include "components.hpp"
#include "ecs.hpp"

namespace Player{
	void init(World &world);
	void update(World &world);

	inline void player_move(Position& position, Camera& camera);
};
