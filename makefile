
CXX = g++

CXXFLAGS = -Wall -g

main: obj/main.o obj/vec3.o obj/camera.o obj/material.o obj/texture.o obj/surface.o obj/light.o obj/scene.o
	$(CXX) $(CXXFLAGS) obj/main.o obj/vec3.o obj/camera.o obj/material.o obj/texture.o obj/surface.o obj/light.o obj/scene.o -o main

obj/vec3.o: vec3.h vec3.cpp | obj
	$(CXX) $(CXXFLAGS) -c vec3.cpp -o obj/vec3.o

obj/camera.o: camera.h camera.cpp bmp.h | obj
	$(CXX) $(CXXFLAGS) -c camera.cpp -o obj/camera.o

obj/material.o: material.h material.cpp | obj
	$(CXX) $(CXXFLAGS) -c material.cpp -o obj/material.o

obj/texture.o: texture.h texture.cpp | obj 
	$(CXX) $(CXXFLAGS) -c texture.cpp -o obj/texture.o

obj/surface.o: surface.h surface.cpp | obj
	$(CXX) $(CXXFLAGS) -c surface.cpp -o obj/surface.o

obj/light.o: light.h light.cpp | obj
	$(CXX) $(CXXFLAGS) -c light.cpp -o obj/light.o

obj/scene.o: scene.h scene.cpp | obj
	$(CXX) $(CXXFLAGS) -c scene.cpp -o obj/scene.o

obj/main.o: main.cpp | obj
	$(CXX) $(CXXFLAGS) -c main.cpp -o obj/main.o

obj:
	mkdir obj

clean:
	del main.exe obj\*.o *.bmp *.ppm 
	rmdir obj