#include "Timer.h"
#include <ctime>

using namespace std;


Timer::Timer()
{
	prev = clock();
	cur = prev;
	t = 0;
	dt = 0;
	fps = 0;
}

float Timer::update()
{
	prev = cur;
	cur = clock();
	dt = (cur - prev) / (float)CLOCKS_PER_SEC;
	t += dt;
	fps = 1 / dt;
	return dt;
}


Timer::~Timer()
{
}
