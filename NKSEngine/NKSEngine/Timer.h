#pragma once
#include <ctime>

using namespace std;

class Timer
{
private:
public:
	clock_t cur, prev;
	float t;
	float dt;
	float fps;
	Timer();
	float update();
	virtual ~Timer();
};

