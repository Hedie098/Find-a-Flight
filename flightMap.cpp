//Implement the flightMap class defined in flightMap.h
#include "flightMap.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string.h>
#include "type.h"
#include<bits/stdc++.h>


using namespace std;


// implement the methods of the flightMap class here

//constructor
FlightMapClass::FlightMapClass()
{
	//taking an object from the vector by calling constructor
	cities = vector<string>();
	visited = vector<bool>();
	size = 0;
	map = NULL;
}

//copy constructor
FlightMapClass::FlightMapClass(const FlightMapClass &f)
{
	size = f.size;
	cities = f.cities;
	map = new list<flightRec>(size);
	//storing the passed flighRecord into the original one (taking a copy
	//of the list of flight records for each city)
	for(int i = 0; i < size; i++)
		{
			map[i] = f.map[i];
		}
	visited = f.visited;
}

//deconstructor
FlightMapClass::~FlightMapClass()
{
	delete[] map;
	cities.clear();
	visited.clear();
}

void FlightMapClass::ReadCities(ifstream &citiesFile)
{
	int fileSize;
	string tempString;

	//get fileSize
	citiesFile >> fileSize;
	size = fileSize;
	
	for(int i = 0; i < fileSize; i++)
		{
			getline(citiesFile, tempString);
			//push back is an object of vector, pushes back the line/city to the end of the vector, vector does not have
			//a size, the vector is more useful than a 2d array because we will use less space
			cities.push_back(tempString);
		}
	//sort the cities alphabetically
	sort(cities.begin(), cities.end());
	// for(int i = 0; i < numCities; i++)
	// 	{
	// 		cout << cities[i] << endl;
	// 	}
	// int index = 0;
	// for(auto elem: cities)
	// 	{
	// 		flightMap[index].cityName = elem;
	// 	}
}



//Reads flight information and build the adjacency list
//Pre-condition: list of the flight information is provided
//Post-condition: Flight map is built
void FlightMapClass::BuildMap(ifstream &flightRecordsFile)
{
	string line;
	string independantLine;
	int flightNumber;
	string takeoffCity;
	string arrivalCity;
	int cost;

	

	
	//allocate flight map, with the size we need based on numCities
	map = new list<flightRec>[size];
	
	//how many elements we want in the visited vector, and set all values to false
	//because all cities will be unvisited in the first place
	visited = vector<bool>(size,false);

	
	while(true)
	{
	if(!(flightRecordsFile >> flightNumber))
	{
		break;
	}
	//parameterize the 4 different values in the flightRecord
	flightRecordsFile >> takeoffCity;
	flightRecordsFile >> arrivalCity;
	flightRecordsFile >> cost;

	flightRec record;
	record.flightNum = flightNumber;
	record.origin = takeoffCity;
	record.destination = arrivalCity;
	record.price = cost;

	//check the index of the city of the origin of the flight
	for(int i = 0; i < size; i++)
		{
			if(cities[i] == takeoffCity)
			{
				//storing the flightRec inside the list of the flights with the same origin 
				map[i].push_back(record);
			}
		}
	}
}

	// while(getline(flightRecordsFile, line))
	// 	{
	// 		//store the line inside stream
	// 		istringstream ss(line);
	// 		//storing the flight record inside the current flight
	// 		flightRec *currentFlight = new struct flightRec;

	// 		//parameterize the stream into 4 different values
	// 		ss >> currentFlight->flightNum;
	// 		ss >> currentFlight->origin;
	// 		ss >> currentFlight->destination;
	// 		ss >> currentFlight->price;
	// 		//cout << record << endl;
	//    //  cout << record.flightNum << " " << record.origin << " " <<
	// 			// record.destination << " " << record.price << endl << endl;

	// 		//for each flight record you need a new connected flight
	// 		//structutre
	// 		// struct connectedFlights *current = new struct connectedFlights;
	// 		// current->data = record;
			
	// 		//find the city name on the flight map array
	// 		for(int i = 0; i < size; i++)
	// 			{
	// 				//find the index of the origin inside the flight map
	// 				if(currentFlight->origin == cities[i])
	// 				{
	// 					//check if startOfFlights is null or not(empty or not)
	// 					if(map[i] == NULL)
	// 					{
	// 						map[i] = *currentFlight;
	// 					}
	// 					//assigning lastFlight to the last flight in the connected flights
	// 					else
	// 					{
	// 						struct flightRec *lastFlight = map[i].nextFlight;
	// 						while(lastFlight != NULL)
	// 							{
									
	// 								if(lastFlight->nextFlight == NULL)
	// 								{
	// 									lastFlight->nextFlight = currentFlight;
	// 									break;
	// 								}
	// 								//if current flight is not the last flight
	// 								else 
	// 								{
	// 									lastFlight = lastFlight->nextFlight;
	// 								}
	// 							}
	// 					}
	// 					}
	// 				}
	// 		}
		
	// }


void FlightMapClass::DisplayMap()
{
	cout << "Flight num " << "From " << "Destination " << "Cost" << endl;

	
	for(int i = 0; i < size; i++)
		{
			if(map[i].size() != 0)
			{
			list <flightRec>::iterator it;
			for(it = map[i].begin();  it != map[i].end(); ++it)
				{
					cout << *it;
					//cout << it->flightNum << " " << it->origin << " " <<
						//it->destination << " " << it->price << endl;
				}
			}
		}
}

bool FlightMapClass::CheckCity(string cityName) const
{
	
  // Check whether a city is in the cities that EastWest airline serves.
	// Pre-condition: cityName to be checked is provided
  // Post-condition: return true if the city is in the cities array
	for(int i = 0; i < size; i++)
		{
			if(cityName == cities[i])
			{
				return true;
			}
		}
	return false;
}

void FlightMapClass::DisplayAllCities() const
  // Displays all of the cities
{
	cout << "These are the cities that we have: " << endl;
	for(int i = 0; i < size; i++)
		{
			cout << cities[i] << endl;
		}
}

void FlightMapClass::MarkVisited(int city)
  // Marks a city as visited
  // Pre-condition: city to be marked as visited is provided
  // Post-condition: a city is marked as visited
{
	visited[city] = true;
}

void FlightMapClass::UnvisitAll()
  // Clears marks on all cities
  // Pre-condition: there are > 0 cities in a cities array
  // Post-condition: all cities marked as unvisited
{
	for(int i = 0; i < size; i++)
		{
			visited[i] = false;
		}
}

bool FlightMapClass::IsVisited(int city) const
  // Determines whether a city was visited
  // Pre-condition: city is provided
  // Post-condition: return true if city has been visited
  //              otherwise return false
{
	//alternate
	//return visited[city];
	
	if(visited[city] == true)
	{
		return true;
	}
	return false;
}

int FlightMapClass::GetCityNumber(string cityName) const
  // returns the integer index corresponding to a city name
  // Pre-condition: name of a city is provided
  // Post-condition: returns the index number corresponding to a city name
{
	for(int i = 0; i < size; i++)
		{
			if(cities[i] == cityName)
			{
				return i;
			}
		}
}

string FlightMapClass::GetCityName(int cityNumber) const
  // returns the name of a city given its corresponding index
  // Pre-condition: number of a city is provided
  // Post-condition: returns the city's name
{
	return cities[cityNumber];
}

bool FlightMapClass::GetNextCity(string fromCity, string &nextCity)
  // Determines the next unvisited city, if any,
  // that is adjacent to a given city.
  // success indicates whether an unvisited adjacent city was found
  // Pre-condition: topCity and nextCity provided
  // Post-condition: return true if an unvisited adjacent city was found
  //              otherwise return false
{
	
		int cityIndex;
		cityIndex = GetCityNumber(fromCity);
				if(map[cityIndex].size() != 0)
				{
					list<flightRec>::iterator it;
					for(it = map[cityIndex].begin(); it != map[cityIndex].end(); ++it)
						{
							//find the index of the destination in the cities
							int destinationIndex;
							destinationIndex = GetCityNumber(it->destination);
							//check if this index, which should match the indexes in
							//you IsVisited function, is true or false;
							bool validDestination;
							validDestination = IsVisited(destinationIndex);
							if(!validDestination)
							{
								nextCity = it->destination;
								return true;
							}
						}
					//if you could not find a destination that is unvisited
					//after checking all of the flights
					return false;
				}
	return false;
}

void FlightMapClass::FindPath(string originCity, string destinationCity)
  // Determines whether a sequence of flights between two cities exists.
  // Pre-condition: originCity and destinationCity are the origin and destination city, respectively
  // Post-condition: returns true if a sequence of flights exists
  //              from origin to destination; otherwise return false.
  //              Cities visited during the search are marked as visited
  //              in the flight map
{
	
	stack<string> searchStack;
	vector<string> path;
	string nextCandidate;
	

	
	//To renew you depth search
	UnvisitAll();

	
	MarkVisited(GetCityNumber(originCity));
	searchStack.push(originCity);
	
	while(!searchStack.empty())
		{
			
			//found an adjacent unvisited node at the top of the stack
			if(GetNextCity(searchStack.top(), nextCandidate))
			{

				//if you found the destination, then pop all values
				//into a vector
				if(nextCandidate == destinationCity)
				{
					while(!searchStack.empty())
						{
							//take a peek at the top value of the stack, (last value that
							//entered the stack) and push it back into the vector
							path.push_back(searchStack.top());
							//pop city from stack so that you may continue your popping until
							//the stack is empty
							searchStack.pop();
						
						}
					//reverse the vector because you pop it from the top of the stack
					//which means they will be stored in the vector in reverse order
					reverse(path.begin(), path.end());
					path.push_back(destinationCity);
					

					
					// //print path
					// for(int i = 0; i < path.size(); i++)
					// 	{
					// 		//get the index of the city that you want to loop over 
					// 		//to get the list of flights from that city
					// 		for(int j = 0; j < map[GetCityNumber(path[i])].size(); j++)
					// 			{
					// 				cout << path[i] << " ->";
					// 			}
							
					// 	}
				int totalCost = 0;
				cout << "BlueSky airline serves between these two cities: " << endl;
				cout << "Flight# " << "From " << "To " << "Cost " << endl;
				//print path
				for(int i = 0; i < path.size() - 1; i++)
					{
						int indexCity = GetCityNumber(path[i]);
						list<flightRec>::iterator it;
						for(it = map[indexCity].begin(); it != map[indexCity].end(); ++it)
							{
								if(it ->destination == path[i + 1])
								{
									cout << *it;
									totalCost += it->price;
									break;
								}
							}
					}

					cout << "Total: " << "   $" << totalCost << endl << endl;


					
					
					//when the path is found do not print all the paths but just 
					//the sought path
					return;
				}
				//if destination is not found
				else
				{
					
					searchStack.push(nextCandidate);
					MarkVisited(GetCityNumber(nextCandidate)); 
				}
			}
			//else of the outer if
			//pop the top of the stack if it has no adjacency
			else
			{
				searchStack.pop();
			}
		}
	//if there is no path
	cout << "Sorry, BlueSky airline does not fly from "  << originCity <<
		" to " << destinationCity << endl << endl;
}

