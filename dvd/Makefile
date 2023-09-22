CXX = g++
CXXFLAGS = -std=c++11 -I /usr/local/include
LDFLAGS = -L /usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
OUTPUT = run

all: 
	$(CXX) $(CXXFLAGS) main.cpp -o $(OUTPUT) $(LDFLAGS)

clean: 
	rm $(OUTPUT)

