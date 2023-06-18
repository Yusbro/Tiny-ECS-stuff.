#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <iostream>



class Archtype
{
public:
	std::unordered_map<std::string, void*> data;
	Archtype(){}
	~Archtype(){}	
};


class World
{

private:
	int max_arch_size = 20;
	std::vector<std::unique_ptr<Archtype>> archtypes;
	std::unordered_map<std::size_t, int> type_manager;
	std::unordered_map<std::string, std::vector<int>> component_manager;
	
	
	void Register_Components(std::string type_name, int archtype_location)
	{
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
	void Remove_Archtype()
	{
		std::vector<int> arch_id = Get_Archtype<T...>();

		([&](){
			std::string type_name = typeid(T).name();
			void* data_pointer = archtypes[arch_id[0]]->data[type_name];
			std::vector<T>* vec_data = static_cast<std::vector<T>*>(data_pointer);

			delete vec_data;	
		}(),...);	
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
		(type_names.push_back(typeid(T).name()),...);
		
		std::vector<int> temp(max_arch_size, -1);
		
		int counter=0;
		//newer stuff!!
		for(std::string i : type_names){
			for(int j=0;j<max_arch_size;j++){
				if(counter==0) temp[j] = component_manager[i][j];
				if(temp[j] != component_manager[i][j]) temp[j] = -1;
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

	template <class T>
	std::vector<T>* Fetch_Data(int i)
	{
		void* data_pointer = archtypes[i]->data[typeid(T).name()];
		return static_cast<std::vector<T>*>(data_pointer);
	}
};

