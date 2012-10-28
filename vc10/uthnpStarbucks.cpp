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
		if(data->x < this->entry->x)
		{
			if (this->left == NULL)
			{
				this->left = new uthnpStarbucks(data);
				return;
			}
			else this->left->add(data, !isX);
		}
		else
		{
			if (this->right == NULL)
			{
				this->right = new uthnpStarbucks(data);
				return;
			}
			else this->right->add(data, !isX);
		}
	}
	else
	{
		if(data->y < this->entry->y)
		{			
			if (this->left == NULL)
			{
				this->left = new uthnpStarbucks(data);
				return;
			}
			else this->left->add(data, !isX);
		}
		else
		{
			if (this->right == NULL)
			{
				this->right = new uthnpStarbucks(data);
				return;
			}
			else this->right->add(data, !isX);
		}
	}
}

void uthnpStarbucks::randomizeArray (Entry* input, int len)
{
}

void uthnpStarbucks::build(Entry* c, int n)
{
}

Entry* uthnpStarbucks::getNearest(double x, double y)
{
	return NULL;
}
