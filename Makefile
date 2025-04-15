build: 
			 g++ -Wall -std=c++17 ./src/*.cpp ./src/glad.c -I./include -lSDL2 -ldl -lGL -o renderer 


run: 
			./renderer 

clean: 
			rm renderer
