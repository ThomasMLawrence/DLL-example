#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;
//Michael Lawrence


//this file holds the class declarations of
//the nodes used in the data structures of this
//program and the class that holds the data
//that resides in those nodes.


class position
{
	public:
		position();
		//pass in a 1 to make the space your car.
		//pass in another number to randomly generate
		//1/3 another car 2/3 empty.
		position(int command);
		//randomly generates car or empty with
		//the above chances.
		void random();
		//returns the id.
		char get();
		//manually set the id.
		//'u' is your car
		//'c' is another car
		//'x' is empty.
		void set(char to_set);
		//if it is empty returns true.
		//occupied false.
		bool valid();
	protected:
		char id;
};

class node: public position
{
	public:
		node();
		node(int id);
		//pass in a 1 to make the space your car.
		//pass in another number to randomly generate
		//1/3 another car 2/3 empty.	
		node(const position & to_copy);
		//returns the next pointer
		node * & go_next();
		//points the next pointer to the pointer
		//passed in. Pass in NULL to make this node
		//the end of your list.
		void set_next(node * next_node);
	private:
		node * next;
};
