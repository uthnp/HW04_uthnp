#pragma once
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