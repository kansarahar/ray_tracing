
CXX = g++

CXXFLAGS = -Wall -g

main: main.o vec3.o camera.o sphere.o
	$(CXX) $(CXXFLAGS) main.o vec3.o camera.o sphere.o -o main

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

vec3.o: vec3.h vec3.cpp
	$(CXX) $(CXXFLAGS) -c vec3.cpp -o vec3.o

camera.o: camera.h camera.cpp 
	$(CXX) $(CXXFLAGS) -c camera.cpp -o camera.o

sphere.o: surface.h surfaces/sphere.cpp
	$(CXX) $(CXXFLAGS) -c surfaces/sphere.cpp -o sphere.o


clean:
	rm main *.o