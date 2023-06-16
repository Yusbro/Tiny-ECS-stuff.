#include "ecs.hpp"
#include "asset_data.hpp"

class Game{
	World world;
	AssetData asset_data;

	public:
		Game();
		~Game();
		
		void init();
		void update();
		void draw();
		void deinit();
};
