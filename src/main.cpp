#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <typeindex>
#include <string>
#include <memory>
#include <algorithm>

struct Position
{
	int id;
	Vector3 position;
};

struct RigidBody
{
	int id;
	float mass;
	Vector3 velocity;
};


struct Circle{
	int id;
	float Radius;
};

struct Box{
	int id;
	float Size;
};




class Archtype
{
public:
	std::unordered_map<std::string, void*> data;
	Archtype(){}
	~Archtype()
	{
		for (auto &i : data)
		{
			free(i.second);
		}
	}
};

class World
{
private:
	int max_arch_size = 20;
	std::vector<std::unique_ptr<Archtype>> archtypes;
	std::unordered_map<std::string, std::vector<int>> component_manager;
	
	
	void Register_Components(std::string type_name, int archtype_location){
		if(!component_manager.count(type_name) > 0){
			component_manager.insert({type_name, std::vector<int>(max_arch_size, -1)});
		}
		component_manager[type_name][archtype_location] = archtype_location;
	}


public:
	World() {}
	~World() {}

	template <class... T>
	int Add_Archtype()
	{
		std::unique_ptr<Archtype> temp_arch = std::make_unique<Archtype>();

		([&](){
			temp_arch->data.insert({
					typeid(T).name(),
					static_cast<void*>(new std::vector<T>())
					});
		 }(),...);
		archtypes.push_back(std::move(temp_arch));
	

		(Register_Components(typeid(T).name(), archtypes.size()-1),...);
		return archtypes.size()-1;
	}

	template <class... T>
	void Add_Entity(int arch_loc, T... val)
	{	
		([&](){
			void* data_pointer = archtypes[arch_loc]->data[typeid(T).name()];
			std::vector<T>* data_vector = static_cast<std::vector<T>*>(data_pointer);
			data_vector->push_back(val);
		 }(),...);
	}

	template <class... T>
	std::vector<int> Get_Archtype()
	{	
		std::vector<std::string> type_names;
		([&](){
			type_names.push_back(typeid(T).name());
		 }(),...);
		
		std::vector<int> temp(max_arch_size, -1);
		
		int counter=0;
		//newer stuff!!
		for(std::string i : type_names){
			for(int j=0;j<max_arch_size;j++){
				if(counter==0){
					temp[j] = component_manager[i][j];
				}
				
				if(temp[j] != component_manager[i][j]){
					temp[j] = -1;	
				}
			}
			counter++;
		}
		std::vector<int> ret;
		for(int i:temp){
			if(i<0) continue;
			ret.push_back(i);
		}
		return ret;
	}

	void* fetch_arch_data(int i,std::string name){
		return archtypes[i]->data[name];
	}
};

int main()
{
	World world;
	
	int static_box = world.Add_Archtype<Position, Box>();
	int dynamic_box = world.Add_Archtype<Position, Box, RigidBody>();		
	


	for(int i=0;i<100;i++){
		Vector3 position = {(float)GetRandomValue(0, 800), (float)GetRandomValue(0, 600), 0};
		world.Add_Entity<Position, Box>(static_box, (Position){0, position}, (Box){0, 5});


		Vector3 _position = {(float)GetRandomValue(0, 800), (float)GetRandomValue(0, 600), 0};
		world.Add_Entity<Position, Box, RigidBody>(dynamic_box, (Position){0, _position}, (Box){0, 10}, (RigidBody){0, 4, (Vector3){1,0,0}});
	}


	std::vector<int> s = world.Get_Archtype<Position, Box>();
	


	InitWindow(800, 600, "Happy bday yuuu boo!!");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
			ClearBackground(BLUE);	
			for(int i : s){
				void* pos = world.fetch_arch_data(i, typeid(Position).name());
				void* box = world.fetch_arch_data(i, typeid(Box).name());
				
				std::vector<Position>* pos_vec = static_cast<std::vector<Position>*>(pos);	
				std::vector<Box>* box_vec = static_cast<std::vector<Box>*>(box);
				for(int j=0;j<pos_vec->size(); j++){
					DrawRectangle((*pos_vec)[j].position.x, (*pos_vec)[j].position.y, (*box_vec)[j].Size, (*box_vec)[j].Size, RED);	
				}	
			}

		EndDrawing();
	}
	CloseWindow();
	return 0;
}
