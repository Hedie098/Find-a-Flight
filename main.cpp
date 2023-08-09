// if late, give reason and pass # here
/* 
 PROGRAMMER:       	Hedie Yazdanparast
 Program Description:    
  We are reading the flight requests from the file provided. Then we build an
  adjacency list in order to know the flights from one city to other cities.
  In order to find the path from one city to another we use the depth first
  algorithm.
*/ 

#include <iostream>
#include "flightMap.h"



int main() 
{
	//open cities file
	ifstream citiesFile;
	citiesFile.open("cities.dat");

	//open flightRecords
	ifstream flightRecordsFile;
	flightRecordsFile.open("flights.dat");

	//open requests file
	ifstream requestFiles;
	string origin, destination;
	requestFiles.open("requests.dat");
	
	FlightMapClass fmc;
	fmc.ReadCities(citiesFile);
	
	fmc.BuildMap(flightRecordsFile);
  
	//fmc.DisplayMap();
	
	//fmc.DisplayAllCities();

	//read origins and destinations from the requests file
	while(requestFiles >> origin)
		{
			requestFiles >> destination;
			cout << "Reqeust is to fly from " << origin << " to " << destination 
				<< endl;
			fmc.FindPath(origin, destination);
		}
	
	return 0;
}