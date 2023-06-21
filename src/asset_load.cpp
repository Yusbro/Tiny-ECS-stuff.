#include "../include/asset_load.hpp"
#include <fstream>
#include "../include/json.hpp"

using json = nlohmann::json;

void Asset_Loader::load_shader(AssetData &asset_data)
{
	asset_data.shader = LoadShader("", "asset/shader/world.fs");
}

void Asset_Loader::load_models(AssetData &asset_data)
{	
	std::ifstream f("asset/asset.json");
	
	
	std::string fileContent({std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>()});
	
	std::cout<<fileContent<<std::endl;

	json data = json::parse(fileContent);
	std::cout<<"asset json parased!"<<std::endl;

	if(data.contains("models") && data["models"].is_object()){
		for(auto i = data["models"].begin(); i != data["models"].end(); i++ ){
			std::string k = i.key();
			std::cout<<"[ASSET LOAD] loaded "<<k<<std::endl;
			const json value = i.value();//the path array!!!
			
			std::string model_path = value[0];
			std::string texture_path = value[1];//"asset/models/ground_tex.png";

			Model model = LoadModel(model_path.c_str());
			Texture2D texture = LoadTexture(texture_path.c_str());
			
			model.materials[0].shader = asset_data.shader;
			model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

			asset_data.Models.push_back(model);
		}
		std::cout<<"done loading the models"<<std::endl;
	}
}


void Asset_Loader::load_billboard(AssetData &asset_data)
{	
	std::ifstream f("asset/asset.json");	
	
	std::string fileContent({std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>()});
	
	std::cout<<fileContent<<std::endl;

	json data = json::parse(fileContent);
	std::cout<<"asset json parased!"<<std::endl;

	if(data.contains("billboard") && data["billboard"].is_object()){
		for(auto i = data["billboard"].begin(); i != data["billboard"].end(); i++ ){
			std::string path = i.value();
			
			Texture texture = LoadTexture(path.c_str());
			asset_data.Billboard.push_back(texture);
		}
		std::cout<<"done loading the billboard"<<std::endl;
	}
	

}
