#include <vector>
#include <iostream>
#include <unordered_map>
#include <typeindex>
#include <string>

class Arch{
	public:
		std::unordered_map<int, void*> data2;
		std::unordered_map<std::string, void*> data3;

		~Arch(){
			for(auto &i:data2){
				free(i.second);
			}

			for(auto &i:data3){
				free(i.second);
			}
		}
};


class World{

	public:
		Arch arch;
		

		template <class... T>
		void init(){
			arch.data2.insert({
					0,
					static_cast<void*>(new std::vector<int>())
					});

			([&](){
				arch.data3.insert({
						typeid(T).name(),
						static_cast<void*>(new std::vector<T>())
						});

			 }(),...);
		}

		
	
		
		template <class T>
		void add(T val){
			void* data2 = arch.data2[0];
			std::vector<T>* num2 = static_cast<std::vector<T>*>(data2);
			
			num2->push_back(val);
		}
	
		template <class... T>
		void add2(T... val){
			([&](){
				void* data2 = arch.data3[typeid(T).name()];
				std::vector<T>* num3 = static_cast<std::vector<T>*>(data2);
				num3->push_back(val);
			 }(),...);
		}


		
		template <class T>
		void show(){	
			void* data2 = arch.data2[0];
			std::vector<T>* num2 = static_cast<std::vector<T>*>(data2);
			for(auto i: (*num2)){
				std::cout<<i<<std::endl;
			}
		}


		template <class... T>
		void show2(){
			([&](){
				void* data = arch.data3[typeid(T).name()];
				std::vector<T>* num3 = static_cast<std::vector<T>*>(data);
				for(auto i:(*num3)){
					std::cout<<i<<std::endl;	
				}
			 }(),...);
		}

};



struct _Arch{
	std::unordered_map<std::string, std::vector<int>> dict;
};



int main(){
	std::vector<_Arch> data;
	


	return 0;
}
