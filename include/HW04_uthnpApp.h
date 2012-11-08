#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "Starbucks.h"
#include "uthnpStarbucks.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04_uthnpApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings (Settings* settings);
	bool firstRun;
	/*
	*	Converts a string to a double. 
	*	Source: http://www.cplusplus.com/forum/articles/9645/
	*/
	double stringToDouble(string str);
	/*
	* Converts a latidude value to an Y coordinate based on:
	*	y = (lat+125)/62
	*/
	double latitudeToY (double lat);
	/*
	* Converts a longtitude value to an x coordinate based on:
	*	x = (lon-24)/25
	*/
	double longtitudeToX (double lon);
	/*
	* Goes through the starbuck kd tree structure, finds the coordinates of each starbucks and draws a point on the
	* surface object at those coordinates.
	*/
	void starbucksOnSurface (uthnpStarbucks* root, uint8_t* surfData, int len);

private:
	Surface* mySurface_;
	//Width and height of the screen
	static const int kAppWidth=600;
	static const int kAppHeight=600;
	static const int kTextureSize=1024; // must be power of 2
};