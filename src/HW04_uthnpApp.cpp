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
	for (int i = 1; i < vect->size(); i++)
	{
		entryArray[i] = *(vect->at(i));
	}
	delete vect;

	//call build function with the array and length.
	uthnpStarbucks* root = new uthnpStarbucks();
	(*root).build(entryArray,len);

	//draw the starbucks locations on a surface
	//mySurface_ = new Surface(kTextureSize,kTextureSize,false);
	//Surface mapIMG (loadImage(loadResource(MAP_IMG)));
	mySurface_ = new Surface(loadImage(loadResource(MAP_IMG)));

	uint8_t* pixels = (*mySurface_).getData();
	starbucksOnSurface(root, pixels);
	
}

void HW04_uthnpApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
}

void HW04_uthnpApp::mouseDown( MouseEvent event )
{
}

void HW04_uthnpApp::update()
{
}

void HW04_uthnpApp::draw()
{
	gl::draw(*mySurface_);
	//gl::draw(

	//recurse through the starbucks tree and draw a point for every starbucks location
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

void HW04_uthnpApp::starbucksOnSurface (uthnpStarbucks* root, uint8_t* surfData)
{
	if (root == NULL) {return;}

	Entry* data = root->entry;

	double x = kAppWidth * (*data).x;
	double y = kAppHeight * (*data).y;
	int index = (int)(3*(x + (y*kAppWidth)));
	if (index >= 0)
	{
		surfData[index] = 255;
		surfData[index+1] = 255;
		surfData[index+2] = 0;
	}
	starbucksOnSurface(root->left, surfData);
	starbucksOnSurface(root->right, surfData);
}

CINDER_APP_BASIC( HW04_uthnpApp, RendererGl )
