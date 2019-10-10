CXX = g++
CXXFLAGS = -Wall -Wextra -Werror
DEBUG = -g
OBJS = main.o car.o node.o 

make: $(OBJS)
	$(CXX) $(CXXFLAGS) -o roadSim $(OBJS)

debug: *.cpp
	$(CXX) $(CXXLFAGS) $(DEBUG) -o roadSim *.cpp

clear:	
	rm -rvf roadSim $(OBJS)

clean:
	rm -rvf roadSim
