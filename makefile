
CXX = g++

CXXFLAGS = -Wall -g

main: main.o vec3.o camera.o sphere.o plane.o pointlight.o directionallight.o ambientlight.o scene.o
	$(CXX) $(CXXFLAGS) main.o vec3.o camera.o sphere.o plane.o pointlight.o directionallight.o ambientlight.o scene.o -o main

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

vec3.o: vec3.h vec3.cpp
	$(CXX) $(CXXFLAGS) -c vec3.cpp -o vec3.o

camera.o: camera.h camera.cpp bmp.h
	$(CXX) $(CXXFLAGS) -c camera.cpp -o camera.o

sphere.o: surface.h surfaces/sphere.h surfaces/sphere.cpp
	$(CXX) $(CXXFLAGS) -c surfaces/sphere.cpp -o sphere.o

plane.o: surface.h surfaces/plane.h surfaces/plane.cpp
	$(CXX) $(CXXFLAGS) -c surfaces/plane.cpp -o plane.o

pointlight.o: light.h lights/pointlight.h lights/pointlight.cpp 
	$(CXX) $(CXXFLAGS) -c lights/pointlight.cpp -o pointlight.o

directionallight.o: light.h lights/directionallight.h lights/directionallight.cpp 
	$(CXX) $(CXXFLAGS) -c lights/directionallight.cpp -o directionallight.o

ambientlight.o: light.h lights/ambientlight.h lights/ambientlight.cpp
	$(CXX) $(CXXFLAGS) -c lights/ambientlight.cpp -o ambientlight.o

scene.o: scene.h scene.cpp 
	$(CXX) $(CXXFLAGS) -c scene.cpp -o scene.o
clean:
	del main.exe *.o *.bmp *.ppm