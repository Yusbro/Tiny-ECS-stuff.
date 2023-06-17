#include "ecs.hpp"
#include "asset_data.hpp"

class Game{
	
	private:



		World world;
		AssetData asset_data;
		
		Vector3 camera_center(Camera camera);
		
		RenderTexture render_texture;

	public:
		Game();
		~Game();
		
		void init();
		void update();
		void draw();
		void deinit();
};
