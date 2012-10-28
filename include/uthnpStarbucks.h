/*	
*	@Author Nicholas Uth
*	October 29, 2012 -- CSE 274
*	
*	@Sources: Child class to Starbucks class by Bo Brinkman.
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
	Entry* entry;

	static const int threshold = 0.00001;

	/*
	*	Creates a null node. Can be used as a root or just a basic null tester.
	*/
	uthnpStarbucks();
	/*
	*	Creates a new node with the given Entry data (x,y coords and description)
	*/
	uthnpStarbucks(Entry* data);
	/*
	*	Deletes the contents of the node and the node itself.
	*/
	~uthnpStarbucks();
	/*
	*	Recursively adds a node to the KD tree. Alternatingly sorts the levels based on X or Y coordinate.
	*/
	void add(Entry* data, bool isX);
	/*
	*	Builds an entire tree from an array containing Entry objects.
	*/
	virtual void build(Entry* c, int n);
	/*
	*	Randomizes the order of an array's contents.
	*/
	void randomizeArray (Entry* input, int len);
	/*
	*	Recursively (alternating X and Y) searches the tree for the node containing the closest Starbucks location.
	*/
	virtual Entry* getNearest(double x, double y);
};