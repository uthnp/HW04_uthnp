#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Starbucks.h"
#include "uthnpStarbucks.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04_uthnpApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void HW04_uthnpApp::setup()
{
	vector<Entry*> vect;
	Entry* entryAdding;
	string tempString;
	ifstream locationsFile;
	locationsFile.open("Starbucks_2006.csv", ios::in);
	//read file (for loop) and put data into new entry object. put entry object into vector. note length.
	while (locationsFile.good())
	{
		entryAdding = new Entry();
		getline(locationsFile, entryAdding->identifier, ',');
		getline(locationsFile, tempString, ',');
		entryAdding->x = atof()
	}

	locationsFile.close();
	//transfer vector data to Entry array
	//call build function with the array and length.
	//when finished, call find nearest on series of coordinates.
	//save results
	//...
}

void HW04_uthnpApp::mouseDown( MouseEvent event )
{
}

void HW04_uthnpApp::update()
{
}

void HW04_uthnpApp::draw()
{
	//clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( HW04_uthnpApp, RendererGl )
