#include "HW04_uthnpApp.h"

using namespace ci;
using namespace ci::app;
using namespace std;

void HW04_uthnpApp::setup()
{
	vector<Entry*>* vect = new vector<Entry*>;
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
		vect->push_back(entryAdding);
	}
	locationsFile.close();

	//transfer vector data to Entry array
	Entry* entryArray = new Entry[vect->size()];
	int len = vect->size();
	for (int i = 0; i < len; i++)
	{
		entryArray[i] = *(vect->at(i));
	}
	delete vect;

	//call build function with the array and length. -- For Starbucks
	root = new uthnpStarbucks();
	(*root).build(entryArray,len);

	//draw the starbucks locations on a surface
	//mySurface_ = new Surface(kTextureSize,kTextureSize,false);
	//Surface mapIMG (loadImage(loadResource(MAP_IMG)));
	mySurface_ = new Surface(loadImage(loadResource(MAP_IMG)));

	uint8_t* pixels = (*mySurface_).getData();
	int arrayHeight = max(kAppHeight, kAppWidth);
	arrayHeight *= arrayHeight/kAppWidth;
	starbucksOnSurface(root, pixels, arrayHeight);
	
	//build a tree for the population data in 2000 & 2010
	census2000 = gatherCensusData("Census_2000.csv");
	census2010 = gatherCensusData("Census_2010.csv");

	popChangeVsNumStarb = new Color8u();
}

void HW04_uthnpApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
}

void HW04_uthnpApp::mouseDown( MouseEvent event )
{
	xSelected = event.getX();
	ySelected = event.getY();
}

void HW04_uthnpApp::update()
{
	double x = (1.0 * xSelected)/kAppWidth;
	double y = (1.0 * ySelected)/kAppHeight;
	nearestStarbucks = (*root).getNearest(x, y);

	int popChange = findChangeInPopInRadius(census2000, census2010, x, y, calcRadius);
	int numStarbucks = findNumStarbucksInRadius(root, x, y, calcRadius);
	popChangeVsNumStarb->r = sin((double)popChange/(double)numStarbucks);
	popChangeVsNumStarb->g = cos((double)popChange/(double)numStarbucks);
	popChangeVsNumStarb->b = 0;
}

void HW04_uthnpApp::draw()
{
	gl::color(255,255,255);
	gl::draw(*mySurface_);
	gl::color(*popChangeVsNumStarb);
	gl::drawSolidCircle(Vec2f((float)xSelected, (float)ySelected), calcRadius);
	gl::color(0,255,0);
	gl::drawSolidCircle(Vec2f((float)xSelected, (float)ySelected), 3);
	gl::color(0,100,255);
	float x = (float)(kAppWidth * (*nearestStarbucks).x);
	float y = (float)(kAppHeight * (*nearestStarbucks).y);
	gl::drawSolidCircle(Vec2f(x,y), 3);
}

double HW04_uthnpApp::stringToDouble(string str)
{
	stringstream stream(str);
	double result;
	return stream >> result ? result : 0;
}

double HW04_uthnpApp::latitudeToY (double lat)
{
	return ((lat + 125) / (62));
}

double HW04_uthnpApp::longtitudeToX (double lon)
{
	return (abs(lon - 24) / (25));
}

void HW04_uthnpApp::starbucksOnSurface (uthnpStarbucks* root, uint8_t* surfData, int arrayHeight)
{
	if (root == NULL) {return;}

	Entry* data = root->entry;

	double x = kAppWidth * (*data).x;
	double y = abs(arrayHeight - (kAppHeight * (*data).y));
	int index = 3*(int)(x + (y*kAppWidth));
	if (index >= 0)
	{
		surfData[index] = 255;
		surfData[index+1] = 0;
		surfData[index+2] = 0;
	}
	starbucksOnSurface(root->left, surfData, arrayHeight);
	starbucksOnSurface(root->right, surfData, arrayHeight);
}

uthnpStarbucks* HW04_uthnpApp::gatherCensusData (string file)
{
	vector<Entry*>* vect = new vector<Entry*>;
	Entry* entryAdding;
	string tempString;
	ifstream locationsFile;
	locationsFile.open(file, ios::in);
	//read file and put data into new entry object. put entry object into vector.
	while (locationsFile.good())
	{
		entryAdding = new Entry();
		getline(locationsFile, tempString, ','); //no need
		getline(locationsFile, tempString, ','); //no need
		getline(locationsFile, tempString, ','); //no need
		getline(locationsFile, tempString, ','); //no need

		getline(locationsFile, entryAdding->identifier, ','); //get population
		getline(locationsFile, tempString, ','); //get x value
		entryAdding->x = longtitudeToX(stringToDouble(tempString));
		getline(locationsFile, tempString, '\r'); //get y value
		entryAdding->y = latitudeToY(stringToDouble(tempString));
		vect->push_back(entryAdding);
	}
	locationsFile.close();

	//transfer vector data to Entry array
	Entry* entryArray = new Entry[vect->size()];
	int len = vect->size();
	for (int i = 0; i < len; i++)
	{
		entryArray[i] = *(vect->at(i));
	}
	delete vect;

	uthnpStarbucks* census = new uthnpStarbucks();
	(*census).build(entryArray, len);
	return census;
}

int HW04_uthnpApp::findChangeInPopInRadius (uthnpStarbucks* census1, uthnpStarbucks* census2, int x, int y, int radius)
{
	return 255;
}

int HW04_uthnpApp::findNumStarbucksInRadius (uthnpStarbucks* root, int x, int y, int radius)
{
	if (root == NULL) {return 0;}
	double dx = (root->entry->x) - x;
	double dy = (root->entry->y) - y;
	if (radius < sqrt(dx*dx + dy*dy)) {return 0;}

	return 1 + findNumStarbucksInRadius(root->left, x, y, radius) + findNumStarbucksInRadius(root->left, x, y, radius);
}

CINDER_APP_BASIC( HW04_uthnpApp, RendererGl )
