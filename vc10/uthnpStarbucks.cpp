#include "Starbucks.h"
#include "uthnpStarbucks.h"

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

void uthnpStarbucks::add(Entry* data, bool isX)
{
	if (this == NULL) return;
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
}

Entry* uthnpStarbucks::randomizeArray (Entry* input, int len)
{
	Entry* randArray = new Entry[len];
	int random1;
	int random2;
	Entry* temp;

	for (int i = 0; i < len; i++)
	{
		random1 = (rand() % len);
		random2 = (rand() % len);

		while (random1 == random2)
		{
			random1 = (rand() % len);
			random2 = (rand() % len);
		}
		temp = new Entry();
		temp->identifier = (input[random1].identifier);
		temp->x = input[random1].x;
		temp->y = input[random1].y;

		input[random1] = input[random2];
		input[random2] = *temp;

		delete temp;
	}

	return randArray;
}


void uthnpStarbucks::build(Entry* in, int n)
{
	Entry* c = randomizeArray(in, n);
	this->entry = &(c[0]);

	for (int i = 1; i < 2960; i++)
	{
		this->add(c, true);
	}

}

Entry* uthnpStarbucks::getNearest(double x, double y)
{
	return this->searchMatch(x, y, true);
}

Entry* uthnpStarbucks::searchMatch(double x, double y, bool isX)
{
	if (this == NULL) return this->entry;
	Entry* candidate;

	//recursive part to find candidate... has no return statements
	if(isX)
	{
		if (x <= this->entry->x)
		{
			if (this->left != NULL)
				candidate = this->left->searchMatch(x, y, !isX);
			else
				candidate = this->entry;
		}
		else
		{
			if (this->right != NULL)
				candidate = this->right->searchMatch(x, y, !isX);
			else
				candidate = this->entry;
		}
	}
	else
	{
		if (y <= this->entry->y)
		{
			if (this->left != NULL)
				candidate = this->left->searchMatch(x, y, !isX);
			else
				candidate = this->entry;
		}
		else
		{
			if (this->right != NULL)
				candidate = this->right->searchMatch(x, y, !isX);
			else
				candidate = this->entry;
		}
	}

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
			if (this->right != NULL)
				altCandidate = this->right->searchMatch(x, y, !isX);
			else
				altCandidate = this->entry;
		}
		else
		{
			if (this->left != NULL)
				altCandidate = this->left->searchMatch(x, y, !isX);
			else
				altCandidate = this->entry;
		}
	}
	else if (!isX && (dist > (abs(y - this->entry->y))))
	{
		if (y <= this->entry->y)
		{
			if (this->right != NULL)
				altCandidate = this->right->searchMatch(x, y, !isX);
			else
				altCandidate = this->entry;
		}
		else
		{
			if (this->left != NULL)
				altCandidate = this->left->searchMatch(x, y, !isX);
			else
				altCandidate = this->entry;
		}
	}

	dx = abs(x - altCandidate->x);
	dy = abs(y - altCandidate->y);
	double distAlt = sqrt((dx*dx)+(dy*dy));

	if(dist < distAlt) return candidate;
	else return altCandidate;
}