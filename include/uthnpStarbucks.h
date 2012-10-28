/*	
*	@Author Nicholas Uth
*	October 29, 2012 -- CSE 274
*	
*	Class is intended to work as a KD tree. It handles the coordinates and description of a starbucks and the paths to it's subtrees.
*	
*/

#pragma once

#include <string>
#include "Starbucks.h"

using namespace std;

class uthnpStarbucks : Starbucks
{
public:
	uthnpStarbucks* left;
	uthnpStarbucks* right;
	Entry entry;

	uthnpStarbucks();
	uthnpStarbucks(Entry* data);
	uthnpStarbucks* add(uthnpStarbucks* root, Entry* data, bool isX);
	virtual void build(Entry* c, int n);
	virtual Entry* getNearest(double x, double y);
};