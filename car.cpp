//Michael Lawrence

//a change
//this file contains the class functions
//for the hieararchy map route car
//and the light which route has a "has a"
//relationship with.

#include "car.h"

light::light()
{
	//the light starts 300 feet away and green.
	distance = 300;
	state = 'g';
	time = 0;
}

void light::tick()
{
	time += 1;
	if(time == 1 and state == 'r')
	{
		//the red light only lasts
		//for one tick
		state = 'g';
		time = 0;
	}
	else if(time == 4 and state == 'g')
	{
		//the green light lasts for 5 ticks.
		state = 'r';
		time = 0;
	}
}

void light::step()
{
	//moves the light closer by 100 feet.
	distance -= 100;
	if(distance == 0)
	{
		distance = 300;
	}
}

int light::get_distance()
{
	//returns the distance.
	return distance;
}

char light::get_state()
{
	//returns a g for green and an r for red
	return state;
}

map::map()
{
	lanes = new node* [3];

	for(int i = 0; i < 3; ++i)
	{
		//initializes to NULL;
		lanes[i] = NULL;
	}
	
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			
			
			if(i == 1 && j == 1)
			{
				//the middle spot is initialized
				//to your car.
				node * temp = new node(1);
				temp->set_next(lanes[i]);
				lanes[i] = temp;
			}
			
			else
			{
				//al other spots are initialized
				//to a random car or empty.
				node * temp = new node(2);
				temp->set_next(lanes[i]);
				lanes[i] = temp;

			}
		}
	}
}

map::~map()
{
	for(int i = 0; i < 3; ++i)
	{
		//three destroys for the three LLLs.
		destroy(lanes[i]);
	}
	delete [] lanes;
}

void map::destroy(node * head)
{
	if(!head)
		return;
	//the nodes themselves are deleted in reverse.
	destroy(head->go_next());
	delete head;

}


map::map(const map & to_copy)
{
	lanes = new node * [3];
	for(int i = 0; i < 3; ++i)
	{
		//three recursive copies for each LLL.
		copy(lanes[i], to_copy.lanes[i]);
	}
}

void map::copy(node * & head, node * to_copy)
{
	//recursive copy for one LLL.
	if(!to_copy)
		return;
	//the nodes copy constructor is called.
	head = NULL;
	head = new node(*to_copy);
	copy(head->go_next(), to_copy->go_next());

}

route::route()
{
	location = 4;
	int slot = 0;
	pointers = new node * [9];
	//the pointers are pointed at the appropriate
	//node objects.
	for(int i = 0; i < 3; ++i)
	{
		route_init(slot, lanes[i]);
	}
}

route::~route()
{
	if(pointers)
	{
		//the nodes the pointers point to are
		//deleted in the map destructor. All thats
		//left is to free the array.
		delete [] pointers;
	}

}

route::route(const route & to_copy): map(to_copy)
{
	//9 pointers are pointed at the already copies
	//map that was copied through the initialization
	//list.
	location = 4;
	int slot = 0;
	pointers = new node * [9];
	for(int i = 0; i < 3; ++i)
	{
		route_init(slot, lanes[i]);
	}

}

void route::route_init(int &slot, node * head)
{
	//slot is incremented by reference so that each
	//pointer points to the appropriate location.
	if(!head)
		return;

	pointers[slot] = head;
	route_init(slot += 1, head->go_next());
}

void route::display()
{
	//this function prints the road.
	int distance = next_light.get_distance();
	char state = next_light.get_state();
	char cars [9];
	for(int i = 0; i < 9; ++i)
	{
		//an array of chars is used to quickly print
		//the data in the nodes.
		cars[i] = pointers[i]->get();
	}
	//three distance options place the light in different locations.
	if(distance == 100)
	{
		cout << "|" << cars[2] << "|" << cars[5] << "|" << cars[8] << "|" << endl;
		cout << "|" << state << "|" << state << "|" << state << "|" << endl;
		cout << "|" << cars[1] << "|" << cars[4] << "|" << cars[7] << "|" << endl;
		cout << "|" << cars[0] << "|" << cars[3] << "|" << cars[6] << "|" << endl;
	}
	else if(distance == 200)
	{
		cout << "|" << state << "|" << state << "|" << state << "|" << endl;
		cout << "|" << cars[2] << "|" << cars[5] << "|" << cars[8] << "|" << endl;
		cout << "|" << cars[1] << "|" << cars[4] << "|" << cars[7] << "|" << endl;
		cout << "|" << cars[0] << "|" << cars[3] << "|" << cars[6] << "|" << endl;

	}
	else if(distance == 300)
	{	
		cout << "|" << cars[2] << "|" << cars[5] << "|" << cars[8] << "|" << endl;
		cout << "|" << cars[1] << "|" << cars[4] << "|" << cars[7] << "|" << endl;
		cout << "|" << state << "|" << state << "|" << state << "|" << endl;
		cout << "|" << cars[0] << "|" << cars[3] << "|" << cars[6] << "|" << endl;
	}

}

int route::move_right()
{
	//will you run off the edge of the road.
	if(location + 3 > 8)
		return 0;

	//is a car blocking your path.
	if(!pointers[location + 3]->valid())
	{
		return 1;
	}
	
	//otherwise swap the empty spot for your car
	//and change the location of your car.
	pointers[location + 3]->set('u');
	pointers[location]->set('x');
	location += 3;
	return 2;
}

int route::move_left()
{
	//will you run off the edge of the road.
	if(location - 3 < 0)
		return 0;

	//is a car blocking your way.
	if(!pointers[location - 3]->valid())
	{
		return 1;
	}

	//otherwise swap the empty spot for your car
	//and change the location of your car.
	pointers[location - 3]->set('u');
	pointers[location]->set('x');
	location -= 3;
	return 2;
}

int route::move_up()
{
	//this function moves your car up one block.
	//no new nodes are actually created. Your car
	//ends in the node it started in and the other
	//cars move back and disapear behind and a new row
	//is generated.
	char state = next_light.get_state();
	int distance = next_light.get_distance();
	//the validity of the space directly in front of you.
	bool valid = pointers[location + 1]->valid();
	//if the red light is right in front of you
	//then you can't run it.
	if(state == 'r' && distance == 100)
	{
		return 0;
	}
	//is a car blocking your way.
	else if(!valid)
	{
		return 1;
	}	

	//in order to never create new nodes, the 
	//data which is just chars is shifted.
	//you and the empty slot are switched.
	pointers[location + 1]->set('u');
	pointers[location]->set('x');
	//then all the values are moved back one row
	pointers[0]->set(pointers[1]->get());
	pointers[1]->set(pointers[2]->get());
	pointers[3]->set(pointers[4]->get());
	pointers[4]->set(pointers[5]->get());
	pointers[6]->set(pointers[7]->get());
	pointers[7]->set(pointers[8]->get());
	//a new front row is randomly generated.
	pointers[2]->random();
	pointers[5]->random();
	pointers[8]->random();
	//the light moves forward.
	//and ticks
	next_light.step();
	next_light.tick();
	return 2;
}

int route::stop()
{
	//this function stops the car.
	int success = 0;
	int distance = next_light.get_distance();
	char state = next_light.get_state();
	bool valid = pointers[location - 1]->valid();

	
	if(state == 'g')
	{
		//is the space behind you occupied.
		if(!valid)
			return 0;
		//these if statements moved the car ahead and the
		//cars around you forward one space.
		//the space ahead becomes empty.
		if(location == 1)
		{
			pointers[2]->set('x');
			pointers[5]->set(pointers[4]->get());
			pointers[4]->set(pointers[3]->get());
			pointers[8]->set(pointers[7]->get());
			pointers[7]->set(pointers[6]->get());
		}
		else if(location == 4)
		{
			pointers[5]->set('x');
			pointers[8]->set(pointers[7]->get());
			pointers[7]->set(pointers[6]->get());
			pointers[2]->set(pointers[1]->get());
			pointers[1]->set(pointers[0]->get());
		}
		else if(location == 7)
		{
			pointers[8]->set('x');
			pointers[5]->set(pointers[4]->get());
			pointers[4]->set(pointers[3]->get());
			pointers[2]->set(pointers[1]->get());
			pointers[1]->set(pointers[0]->get());
		}
		//a new line of cars behind is randomly generated.
		pointers[0]->random();
		pointers[3]->random();
		pointers[6]->random();
		success = 1;
	}
	else if(distance == 300 && state == 'r')
	{
		//if the red light is 300 feet away then
		//that means that their is a red light
		//directly behind you. These cars remain
		//stationary. unlike the green light
		//no new cars are generated.
		//on top of that the space behind you does
		//not need to be empty since a red light cuts
		//them off.
		//
		//unique code is need for each possible location to
		//stop your car from being shifted up.
		if(location == 1)
		{
			//the spot ahead of you is empty
			//all other cars shift up.
			pointers[2]->set('x');
			pointers[5]->set(pointers[4]->get());
			pointers[4]->set('x');
			pointers[8]->set(pointers[7]->get());
			pointers[7]->set('x');	
		}

		else if(location == 4)
		{
			pointers[5]->set('x');
			pointers[2]->set(pointers[1]->get());
			pointers[1]->set('x');
			pointers[8]->set(pointers[7]->get());
			pointers[7]->set('x');	
		}
		else if(location == 7)
		{
			pointers[8]->set('x');
			pointers[5]->set(pointers[4]->get());
			pointers[4]->set('x');
			pointers[2]->set(pointers[1]->get());
			pointers[1]->set('x');	
		}
		//the row behind remains as is.	
		success = 1;
	}

	else if(distance == 200 && state == 'r')
	{
		//heres where things get complicated. There
		//is a red light two tiles ahead of you. no
		//cars can advance beyond that point. But it
		//doesn't make sense for every car to stop where
		//they are. Instead they must move forward to fill
		//empty slots at the light but only if the spot is empty.
		//for example
		//|r|r|r|
		//|x|c|x|
		//|u|c|c|
		//|x|c|x|
		//becomes
		//|g|g|g|
		//|x|c|c|
		//|u|c|x|
		//|x|c|x|
		
		if(!valid && pointers[location + 1]->valid())
			//if the space behind you is occupied and there
			//is an empty space ahead of you you need to move
			//up to the light.
			return 0;

		//unique code is needed for each possible location to stop
		//your car from being shifted up.
		if(location == 1)
		{
			if(pointers[5]->valid())
			{
				//if the car in the middle row moves then
				//any car behind it can also move since that
				//space is guaranteed to be empty.
				pointers[5]->set(pointers[4]->get());
				pointers[4]->set(pointers[3]->get());
				pointers[3]->set('x');	
			}	
			//it may seem as though this else if is unnecessary.
			//Isn't this just the same code above. but it is not guaranteed
			//that any cars will move. Every car must check the space ahead
			//before it moves and this is the most efficient way I could come
			//up with.
			else if(pointers[4]->valid())
			{	
				pointers[4]->set(pointers[3]->get());
				pointers[3]->set('x');	
			}
			if(pointers[8]->valid())
			{
				pointers[8]->set(pointers[7]->get());
				pointers[7]->set(pointers[6]->get());
				pointers[6]->set('x');	
			}	
			else if(pointers[7]->valid())
			{	
				pointers[7]->set(pointers[6]->get());
				pointers[6]->set('x');	
			}
		}
		else if(location == 4)
		{
			if(pointers[2]->valid())
			{
				pointers[2]->set(pointers[1]->get());
				pointers[1]->set(pointers[0]->get());
				pointers[0]->set('x');	
			}	
			else if(pointers[1]->valid())
			{	
				pointers[1]->set(pointers[0]->get());
				pointers[0]->set('x');	
			}
			if(pointers[8]->valid())
			{
				pointers[8]->set(pointers[7]->get());
				pointers[7]->set(pointers[6]->get());
				pointers[6]->set('x');	
			}	
			else if(pointers[7]->valid())
			{	
				pointers[7]->set(pointers[6]->get());
				pointers[6]->set('x');	
			}
		}
		else if(location == 7)
		{
			if(pointers[5]->valid())
			{
				pointers[5]->set(pointers[4]->get());
				pointers[4]->set(pointers[3]->get());
				pointers[3]->set('x');	
			}	
			else if(pointers[4]->valid())
			{	
				pointers[4]->set(pointers[3]->get());
				pointers[3]->set('x');	
			}
			if(pointers[2]->valid())
			{
				pointers[2]->set(pointers[1]->get());
				pointers[1]->set(pointers[0]->get());
				pointers[0]->set('x');	
			}	
			else if(pointers[1]->valid())
			{	
				pointers[1]->set(pointers[0]->get());
				pointers[0]->set('x');	
			}
		}
		success = 1;
	}

	else if(distance == 100 && state == 'r')
	{
		//oh boy this ones much easier than the one above.
		//The row of cars ahead of you leaves you behind
		//and a new row is randomly generated as though
		//they turned right and left onto the street.
		pointers[2]->random();
		pointers[5]->random();
		pointers[8]->random();
		//no cars can move beyond the middle row since the light
		//is right in front of you. since you are at the light
		//it is okay if there is a car behind you.
		if(pointers[1]->valid())
		{
			pointers[1]->set(pointers[0]->get());
			pointers[0]->set('x');
		}
		if(pointers[4]->valid())
		{
			pointers[4]->set(pointers[3]->get());
			pointers[3]->set('x');
		}
		if(pointers[7]->valid())
		{
			pointers[7]->set(pointers[6]->get());
			pointers[6]->set('x');
		}
		success = 1;
	}
	next_light.tick();
	return success;
}

int route::forward()
{
	//this function moves all the cars forward.
	char state = next_light.get_state();
	int distance = next_light.get_distance();
	int success = 0;
	//if the light is green no cars get left behind
	//and all cars can move forward. Thus the distance to
	//the next light is decreased making it appear as though
	//all the cars moved forward even though nothing actually
	//moved.
	if(state == 'g')
	{
		next_light.step();
		success = 1;
	}
	else if(state == 'r' && distance == 100)
	{
		//if the light is red the stop function must be called
		//instead. Why write the same code twice.
		success = 0;
	}
	//for these two states the stop and forward functions are
	//actually different, since if the slot ahead of you is empty
	//you can move up, unlike the stop function where you must
	//stop wherever you are.
	else if(state == 'r' && distance == 200)
	{
		//if you move up we need to shift the screen
		//up as well so as to keep your car in the middle
		//row.
		int moved = 0;
		
		//all the cars check if they can move ahead
		//and do so if the spot is empty in a similar
		//fashion to the stop function. But since
		//this time you can move as well it is not
		//necessary to write different code for each
		//location.
		if(pointers[2]->valid())
		{
			if(location == 1)
			{
				//this sets moved to 1 if you moved up.
				moved = 1;
			}
			pointers[2]->set(pointers[1]->get());
			pointers[1]->set(pointers[0]->get());
			pointers[0]->set('x');

		}
		else if(pointers[1]->valid())
		{
			pointers[1]->set(pointers[0]->get());
			pointers[0]->set('x');

		}
		if(pointers[5]->valid())
		{
			if(location == 4)
			{
				
				moved = 1;
			}
			pointers[5]->set(pointers[4]->get());
			pointers[4]->set(pointers[3]->get());
			pointers[3]->set('x');

		}
		else if(pointers[4]->valid())
		{
			pointers[4]->set(pointers[3]->get());
			pointers[3]->set('x');

		}
		if(pointers[8]->valid())
		{
			if(location == 7)
			{
				moved = 1;
			}
			pointers[8]->set(pointers[7]->get());
			pointers[7]->set(pointers[6]->get());
			pointers[6]->set('x');
		}
		else if(pointers[7]->valid())
		{
			pointers[7]->set(pointers[6]->get());
			pointers[6]->set('x');
		}
		if(moved)
		{
			//another difference between the stop function
			//is if your car moved then we must shift
			//the screen as well.
			pointers[0]->set(pointers[1]->get());
			pointers[1]->set(pointers[2]->get());
			pointers[3]->set(pointers[4]->get());
			pointers[4]->set(pointers[5]->get());
			pointers[6]->set(pointers[7]->get());
			pointers[7]->set(pointers[8]->get());
			pointers[2]->random();
			pointers[5]->random();
			pointers[8]->random();
			next_light.step();	
		}
		success = 1;
	}
	else if(state == 'r' && distance == 300)
	{
		//this ones easy. The light is steped towards you to give the
		//illusion of motion without moving data. and the row
		//behind you, cut off by the light, is left behind causing
		//a new row to be generated as though cars turned at the
		//intersection onto the street you are traveling on. 
		next_light.step();
		pointers[0]->random();
		pointers[3]->random();
		pointers[6]->random();
		success = 1;
	}
	if(success)
		//the light is ticked. It is stepped
		//above where necessary.
		next_light.tick();
	return success;
}

car::car()
{
	//default speed and breaking distance
	speed = 25;
	breaking = 100;

}

void car::drive()
{
	//this is the control function that manages
	//all the other functions and provides a user
	//interface. A new data structure could replace
	//the one used and I would not have to change
	//this function.
	int end = 0;
	while(end != 1)
	{
		cout << "1 - forward" << endl;
		cout << "2 - stop" << endl;
		cout << "3 - move up" << endl;
		cout << "4 - left" << endl;
		cout << "5 - right" << endl;
		cout << "6 - quit" << endl;
		int user_input;
		int value;
		cin >> user_input;
		cin.clear();
		cin.ignore(100, '\n');
		//manages user input based on what they want to do.
		if(user_input == 1)
		{
			if(!forward())
			{
				cout << "The light is red. You need to stop." << endl;
			}	
		}
		else if(user_input == 2)
		{
			if(!stop())
			{
				cout << "There is a car behind you. You can't stop." << endl;
			}
		}
		else if(user_input == 3)
		{
			value = move_up();
		       	if(value == 0)
			{
				cout << "The light is red. You need to stop." << endl;
			}	
			if(value == 1)
			{
				cout << "A car is blocking you. You can't move up." << endl;
			}
		}
		else if(user_input == 4)
		{
			value = move_left();
			if(value == 0)
			{
				cout << "You can't go onto the sidewalk." << endl;
			}
			else if(value == 1)
			{
				cout << "The driver needs to retake control. A car blocks your way. Move up or stop." << endl;
			}
		}
		else if(user_input == 5)
		{
			value = move_right();
			if(value == 0)
			{
				cout << "You can't go onto the sidewalk." << endl;
			}
			else if(value == 1)
			{
				cout << "The driver needs to retake control. A car blocks your way. Move up or stop." << endl;
			}
		}
		else
		{
			end = 1;
		}
		//at the end of every loop the road
		//is displayed again.
		if(end != 1)
			display();
	}
}

void car::start()
{
	//some printing to inform the user how it all works.
	//the route is initialized which calls the map initialization
	//function.
	cout << "You are driving at " << speed << " miles per hours." << endl;
	cout << "Your braking distance is " << breaking << " feet." << endl;
	//a key for the map.
	cout << "Key" << endl;
	cout << "x - empty spot" << endl;
	cout << "u - your car" << endl;
	cout << "c - another car" << endl;
	cout << "g - green light" << endl;
	cout << "r - red light" << endl;
	//instructions on how the generation works for grading
	//purposes.
	cout << "Assume there is a crosstreet at every light." << endl;
	cout << "If you are stopped at a red light then a new " << endl;
	cout << "line of cars will be randomly generated " << endl;
	cout << "as though they turned onto the street in front " << endl;
	cout << "of you. The same goes for a row left behind by " << endl;
	cout << "a red light." << endl;
	//the road is displayed initially.
	display();		


}
