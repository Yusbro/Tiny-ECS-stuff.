doit:
	g++ -fsanitize=address -fno-omit-frame-pointer src/*.cpp -lraylib -lasan
