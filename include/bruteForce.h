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

class bruteForce
{
public:
	Entry* findGuaranteedAnswer(Entry* arr, int len, double x, double y);
	double stringToDouble (string str);
};