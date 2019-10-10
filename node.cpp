//Michael Lawrence


//the member functions for the nodes
//and the data in the nodes.

#include "node.h"

position::position()
{
	//the default is an empty slot.
	id = 'x';
}

position::position(int command)
{

	if(command == 1)
	{
		//if 1 sets the square to contain
		//the drivers car.
		id = 'u';
	}
	else
	{
		//otherwise the slot has a 1/3 chance of being
		//another car. Otherwise empty.
		int number = rand() % 3;
		if(number)
		{
			id = 'x';
		}
		else
		{
			id = 'c';
		}
	}
}


void position::random()
{
	//refreshes the slot with the same chance.
	int number = rand() % 3;
	if(number)
	{
		id = 'x';
	}
	else
	{
		id = 'c';
	}
}

bool position::valid()
{
	//if it is empty return true.
	//if occupied return false.
	if(id == 'x')
		return true;
	else
		return false;

}

char position::get()
{
	//returns the id.
	return id;
}

void position::set(char to_set)
{
	//manually sets the id.
	id = to_set;
}

node::node(): next(NULL)
{
}

node::node(int id): position(id), next(NULL)
{
	//start the correct position constructor	
}

node::node(const position & to_copy): position(to_copy), next(NULL)
{
	//copies a node and sets the next to NULL.
}

node * & node::go_next()
{
	//returns the next pointer for traversal.
	return next;
}

void node::set_next(node * next_node)
{
	//points the next node at the passed in pointer
	next = next_node;
}

