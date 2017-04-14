#pragma once
#include <ctime>

using namespace std;

class Timer
{
private:
	clock_t cur, prev;
public:
	float t;
	float dt;
	float fps;
	Timer();
	void update();
	virtual ~Timer();
};

