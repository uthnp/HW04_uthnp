#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Starbucks.h"
#include "uthnpStarbucks.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04_uthnpApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	bool firstRun;
	/*
	*	Converts a string to a double. 
	*	Source: http://www.cplusplus.com/forum/articles/9645/
	*/
	double stringToDouble(string str);
};

void HW04_uthnpApp::setup()
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
		getline(locationsFile, tempString, '\r'); //get y value
		entryAdding->y = stringToDouble(tempString);
		vect.push_back(entryAdding);
	}
	locationsFile.close();

	//transfer vector data to Entry array
	Entry* entryArray = new Entry[vect.size()];
	int len = vect.size();
	for (int i = 1; i < vect.size(); i++)
	{
		entryArray[i] = *(vect.at(i));
	}
	vect.~vector();

	//call build function with the array and length.
	uthnpStarbucks* root = new uthnpStarbucks();
	(*root).build(entryArray,len);

	//when finished, call find nearest on series of coordinates.
	//save results to file

		Entry* temp = root->getNearest(0.125013, 0.349959);
		ofstream saveTo;
		saveTo.open("../save.txt", ios::out);
		
		//saveTo << entryArray[1].identifier << "\t" <<entryArray[1].x << "\t" << entryArray[1].y << endl;
		saveTo << temp->identifier << "\t" <<temp->x << "\t" << temp->y << endl;

		saveTo.close();
		firstRun = false;
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

double HW04_uthnpApp::stringToDouble(string str)
{
	stringstream stream(str);
	double result;
	return stream >> result ? result : 0;
}

CINDER_APP_BASIC( HW04_uthnpApp, RendererGl )
