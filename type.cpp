//Implement the struct type defined in type.h here
#include "type.h"
#include <iostream>

using namespace std;

bool flightRec :: operator < (const flightRec &rhs) const
{
	//the second destination is what is passsed as the argument, the first destination is implicit
	if(destination < rhs.destination)
	{
		return true;
	}
	return false;
}

bool flightRec :: operator == (const flightRec & rhs) const
{
	if(destination == rhs.destination && origin == rhs.origin)
	{
		return true;
	}
return false;
	
}

ostream& operator << (ostream & os, const flightRec & f)
{
	os << f.flightNum << " " << f.origin << " " << f.destination << " " << f.price << endl;
	return os;
}