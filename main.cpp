//Michael Lawrence

//this file holds the main function that
//manages a simulation of a self driving
//car.

#include "car.h"

int main()
{
	srand(time(NULL));
	car my_car;
	my_car.start();
	//car second_car(my_car);
	//second_car.drive();
	my_car.drive();	
	
	cout << "goodbye" << endl;	
	return 0;
}
