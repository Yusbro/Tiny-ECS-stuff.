#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <variant>


class ArchtypeP{
	public:
		std::unordered_map<std::string, void*> data_map;
		
};

template <class... T>
class ArchtypeC:public ArchtypeP{
	

	public:
		std::variant<std::vector<T>...> data;
		~ArchtypeC(){
			std::cout<<"CLEANED----------"<<std::endl;
		}	
};


class World
{
	private:
		int max_arch_size = 20;

		std::vector<ArchtypeP> archtypes;
		std::unordered_map<std::string, std::vector<int>> component_manager;

		
		void Register_Components(std::string type_name, int archtype_location)
		{
			if(!component_manager.count(type_name) > 0){
				component_manager.insert({type_name, std::vector<int>(max_arch_size, -1)});
			}
			component_manager[type_name][archtype_location] = archtype_location;
		}



	public:
		template <class... T>
		int Add_Archtype(){
			ArchtypeC<T...> temp_arch;
			archtypes.push_back(static_cast<ArchtypeP>(temp_arch));
			([&](){
			 	std::cout<<typeid(T).name()<<std::endl;
			 	std::vector<T>* vec_pointer = &std::get<std::vector<T>>(temp_arch.data);
			 	void* data_pointer = static_cast<void*>(vec_pointer);
				temp_arch.data_map.insert({typeid(T).name(), data_pointer});
			}(),...);	
			
			(Register_Components(typeid(T).name(), archtypes.size()-1),...);
			
			std::cout<<"Made an archtype"<<std::endl;
			return archtypes.size() - 1;
		}

		template<class... T>
		void Add_Entity(int arch_loc, T... Val){
			ArchtypeC<T...>* stuff = static_cast<ArchtypeC<T...>*>(&archtypes[arch_loc]);
			
			([&](){
				std::vector<T> vec_data = (std::get<std::vector<T>>(stuff->data));
				vec_data.push_back(Val);
			 }(),...);
			std::cout<<"added an entity"<<std::endl;
		}

		template <class... T>
		std::vector<int> Get_Archtype(){			
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
			void* data_pointer = archtypes[i].data_map[typeid(T).name()];
			return static_cast<std::vector<T>*>(data_pointer);
		}
};

