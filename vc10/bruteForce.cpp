#pragma once
#include "bruteForce.h"

Entry* findGuaranteedAnswer (Entry* arr, int len, double x, double y)
{
	Entry* currentBest = &arr[0];
	Entry* lookingAt;
	double dx = abs(x - currentBest->x);
	double dy = abs(y - currentBest->y);
	double dist = sqrt((dx*dx)+(dy*dy));
	double bestDist = dist;

	for (int i = 1; i < len; i++)
	{
		lookingAt = &arr[i];
		dx = abs(x - lookingAt->x);
		dy = abs(y - lookingAt->y);
		dist = sqrt((dx*dx)+(dy*dy));

		if (dist < bestDist)
		{
			bestDist = dist;
			currentBest = lookingAt;
		}
	}

	return currentBest;
}

double stringToDouble(string str)
{
	stringstream stream(str);
	double result;
	return stream >> result ? result : 0;
}
/*
int main ()
{
	vector<Entry*> vect;
	Entry* entryAdding;
	string tempString;
	ifstream locationsFile;
	locationsFile.open("Starbucks_2006.csv", ios::in);
	//read file and put data into new entry object. put entry object into vector.
	while (locationsFile.good())
	{
		entryAdding = new Entry();
		getline(locationsFile, entryAdding->identifier, ',');
		getline(locationsFile, tempString, ','); //get x value
		entryAdding->x = stringToDouble(tempString);
		getline(locationsFile, tempString, '\n'); //get y value
		entryAdding->y = stringToDouble(tempString);
		vect.push_back(entryAdding);
	}
	locationsFile.close();

	//transfer vector data to Entry array
	Entry* entryArray = new Entry[vect.size()];
	int len = vect.size();
	for (int i = 0; i < vect.size(); i++)
	{
		entryArray[i] = *(vect.at(i));
	}
	

	return -1;
}
*/