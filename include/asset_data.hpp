#pragma once
#include <vector>
#include <raylib.h>


struct AssetData{
	std::vector<Model> Models;
	std::vector<Texture> Billboard;
	Shader shader;

	void unload_models(){
		for(Model m:Models){
			UnloadModel(m);
		}
	}

	void unload_billboard()
	{
		for(Texture m:Billboard)
		{
			UnloadTexture(m);
		}
	}
};

