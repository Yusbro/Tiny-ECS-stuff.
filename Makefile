doit:
	g++ -fsanitize=address -fno-omit-frame-pointer src/*.cpp src/component/*.cpp -lraylib -lasan
