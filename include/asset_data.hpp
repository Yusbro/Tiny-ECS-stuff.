#pragma once
#include <vector>
#include <raylib.h>


struct AssetData{
	std::vector<Model> Models;
	Shader shader;

	void unload_models(){
		for(Model m:Models){
			UnloadModel(m);
		}
	}
};

