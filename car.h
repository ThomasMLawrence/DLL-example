//Michael Lawrence

//this file contains the map route car
//hierarchy and the light class declaration.

#include "node.h"

class light
{
	public:
		light();
		//increments the light. The light is green for 5 and red for 1.
		void tick();
		//decreases the light distance by 100 feet. resets to 300 feet away.
		void step();
		//returns distance.
		int get_distance();
		//returns 'r' for red and 'g' for green.
		char get_state();
	private:
		char state;
		int time;
		int distance;


};

class map
{
	public:
		//creates a three lane road with your car in the middle.
		map();
		~map();
		map(const map & to_copy);

	protected:
		void copy(node *& head, node * to_copy);
		void destroy(node * head);
		node** lanes;
};

class route: public map
{
	public:
		//initializes both the route and the map so you don't have to call map_init()
		route();
		~route();
		route(const route & to_copy);
		//prints the layout of the road.
		void display();
		//returns 0 if you would go on the sidewalk.
		//returns 1 if a car blocks your way.
		//returns 2 if success.
		int move_right();
		//returns 0 if you would go on the sidewalk.
		//returns 1 if a car blocks your way.
		//returns 2 if success.
		int move_left();
		//returns 0 if the light directly in front is red.
		//returns 1 if a car blocks your way
		//returns 2 if success.
		int move_up();
		//returns 0 if a car would hit you from the back
		//returns 1 if success.
		int stop();
		//returns 0 if you are at a red light
		//returns 1 if success
		int forward();
	protected:
		void route_init(int &slots, node * head);
		node ** pointers;
		light next_light;
		int location;

};

class car: public route
{
	public:
		car();
		//a control function that allows the user
		//to move the car. Call it after start.
		void drive();
		//sets up the road by calling the base class
		//inits.
		void start();
	protected:
		int speed;
		int breaking;

};
