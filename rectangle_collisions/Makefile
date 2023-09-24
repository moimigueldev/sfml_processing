CXX = g++
CXXFLAGS = -std=c++17 -I /usr/local/include
LDFLAGS = -L /usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system
OUTPUT = run

all: 
	$(CXX) $(CXXFLAGS) main.cpp -o $(OUTPUT) $(LDFLAGS)

clean: 
	rm $(OUTPUT)

