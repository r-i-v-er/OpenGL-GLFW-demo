windows:
	g++ main.cpp glad.c -mwindows -o2 -L lib/ -I include/ -lglfw3 -lopengl32 -lgdi32  -lmingw32 -o build/main.exe