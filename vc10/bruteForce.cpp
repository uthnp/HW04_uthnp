#pragma once
#include "Starbucks.h"

using namespace std;

class bruteForce
{
public:
	Entry* findGuaranteedAnswer(Entry* arr, int len, double x, double y);
};


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