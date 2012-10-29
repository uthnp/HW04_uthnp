#include "Starbucks.h"
#include "uthnpStarbucks.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


using namespace std;

uthnpStarbucks::uthnpStarbucks()
{
	*this = NULL;
	//this->entry = NULL;
	//this->left = NULL;
	//this->right = NULL;
}

uthnpStarbucks::uthnpStarbucks(Entry* data)
{
	this->entry = data;
	this->left = NULL;
	this->right = NULL;
}

uthnpStarbucks::~uthnpStarbucks()
{
	delete this->entry;
}

/*
void uthnpStarbucks::add(Entry* data, bool isX)
{
	if (this == NULL) {return;}
	if (isX)
	{
		if(data->x <= this->entry->x)
		{
			if (this->left == NULL)
			{
				this->left = new uthnpStarbucks(data);
				return;
			}
			else
			{
				this->left->add(data, !isX);
				return;
			}
		}
		else
		{
			if (this->right == NULL)
			{
				this->right = new uthnpStarbucks(data);
				return;
			}
			else 
			{
				this->right->add(data, !isX);
				return;
			}
		}
	}
	else
	{
		if(data->y <= this->entry->y)
		{			
			if (this->left == NULL)
			{
				this->left = new uthnpStarbucks(data);
				return;
			}
			else
			{
				this->left->add(data, !isX);
				return;
			}
		}
		else
		{
			if (this->right == NULL)
			{
				this->right = new uthnpStarbucks(data);
				return;
			}
			else
			{
				this->right->add(data, !isX);
				return;
			}
		}
	}
	return;
}*/

uthnpStarbucks* uthnpStarbucks::add(Entry* data, bool isX)
{
	if (this == NULL) {return new uthnpStarbucks(data);}
	if ((abs((this->entry->x) - (data->x)) <= threshold) && (abs((this->entry->y) - (data->y)) <= threshold)) {return this;}

	if (isX)
	{
		if(data->x <= this->entry->x)
		{
			this->left = this->left->add(data, !isX);
		}
		else
		{
			this->right = this->right->add(data, !isX);
		}
	}
	else
	{
		if(data->y <= this->entry->y)
		{
			this->left = this->left->add(data, !isX);
		}
		else
		{
			this->right = this->right->add(data, !isX);
		}
	}
	return this;
}

Entry* uthnpStarbucks::randomizeArray (Entry* input, int len)
{
	Entry* randArray = new Entry[len];
	bool* isSelected = new bool[len];
	int random;

	for (int i = 0; i < len; i++)
	{
		random = (rand() % len);

		while (isSelected[random] == true)
		{
			random = (rand() % len);
		}
		isSelected[random] = true;
		randArray[i] = input[random];
	}

	return randArray;
}


void uthnpStarbucks::build(Entry* c, int n)
{
	//Entry* c = randomizeArray(in, n);
	random_shuffle(c, c+n);
	this->entry = &(c[0]);

	for (int i = 1; i < n; i++)
	{
		this->add(c+i, true);
	}

}

Entry* uthnpStarbucks::getNearest(double x, double y)
{
	return this->searchMatch(x, y, true);
}
/*
Entry* uthnpStarbucks::searchMatch(double x, double y, bool isX)
{
	if (this == NULL) {return NULL;}
	if ((abs((this->entry->x) - x) <= threshold) && (abs((this->entry->y) - y) <= threshold)) {return this->entry;}
	//recursive part to find candidate... has no return statements
	if(isX)
	{
		if (x <= this->entry->x)
		{
			candidate = this->left->searchMatch(x, y, !isX);
		}
		else
		{
			candidate = this->right->searchMatch(x, y, !isX);
		}
	}
	else
	{
		if (y <= this->entry->y)
		{
			candidate = this->left->searchMatch(x, y, !isX);
		}
		else
		{
			candidate = this->right->searchMatch(x, y, !isX);

		}
	}
	if (candidate == NULL) {return this->entry;}

	//checks the candidate against the distance to the boundary node.
	// if the boundary is closer, then recurse into the other side of boundary
	//else return the value up one level

	double dx = abs(x - candidate->x);
	double dy = abs(y - candidate->y);
	double dist = sqrt((dx*dx)+(dy*dy));
	Entry* altCandidate;

	// find candidate in alternate section in case the home coords are close to a boundary
	if (isX && (dist > (abs(x - this->entry->x))))
	{
		if (x <= this->entry->x)
		{
				altCandidate = this->right->searchMatch(x, y, !isX);
		}
		else
		{
				altCandidate = this->left->searchMatch(x, y, !isX);
		}
	}
	else if (!isX && (dist > (abs(y - this->entry->y))))
	{
		if (y <= this->entry->y)
		{
				altCandidate = this->right->searchMatch(x, y, !isX);
		}
		else
		{
				altCandidate = this->left->searchMatch(x, y, !isX);
		}
	}
	if (altCandidate == NULL) {altCandidate = this->entry;}

	dx = abs(x - altCandidate->x);
	dy = abs(y - altCandidate->y);
	double distAlt = sqrt((dx*dx)+(dy*dy));

	if(dist < distAlt) {return candidate;}
	else {return altCandidate;}
}*/

Entry* uthnpStarbucks::searchMatch(double x, double y, bool isX)
{
	if (this == NULL) {return NULL;}
	if ((abs((this->entry->x) - x) <= threshold) && (abs((this->entry->y) - y) <= threshold)) {return this->entry;}
	//recursive part to find candidate... has no return statements
	if(isX)
	{
		if (x <= this->entry->x)
		{
			candidate = this->left->searchMatch(x, y, !isX);
		}
		else
		{
			candidate = this->right->searchMatch(x, y, !isX);
		}
	}
	else
	{
		if (y <= this->entry->y)
		{
			candidate = this->left->searchMatch(x, y, !isX);
		}
		else
		{
			candidate = this->right->searchMatch(x, y, !isX);

		}
	}
	if (candidate == NULL) {return this->entry;}

	//checks the candidate against the distance to the boundary node.
	// if the boundary is closer, then recurse into the other side of boundary
	//else return the value up one level

	double dx = abs(x - (candidate->x));
	double dy = abs(y - (candidate->y));
	double dist = sqrt((dx*dx)+(dy*dy));
	Entry* altCandidate = NULL;
	bool nearXBound = (dist > (abs(x - this->entry->x)));
	bool nearYBound = (dist > (abs(y - this->entry->y)));

	// find candidate in alternate section in case the home coords are close to a boundary
	if (isX && nearXBound)
	{
		if (x <= this->entry->x)
		{
				altCandidate = this->right->searchMatch(x, y, !isX);
		}
		else
		{
				altCandidate = this->left->searchMatch(x, y, !isX);
		}
	}
	else if (!isX && nearYBound)
	{
		if (y <= this->entry->y)
		{
				altCandidate = this->right->searchMatch(x, y, !isX);
		}
		else
		{
				altCandidate = this->left->searchMatch(x, y, !isX);
		}
	}
	if (altCandidate == NULL) {altCandidate = this->entry;}

	dx = abs(x - altCandidate->x);
	dy = abs(y - altCandidate->y);
	double distAlt = sqrt((dx*dx)+(dy*dy));

	dx = abs(x - this->entry->x);
	dy = abs(y - this->entry->y);
	double distBound = sqrt((dx*dx)+(dy*dy));

	if (distAlt >= distBound && dist >= distBound)
	{
		return this->entry;
	}
	else if (distAlt < distBound && dist >= distAlt)
	{
		return altCandidate;
	}
	else
	{
		return candidate;
	}
}