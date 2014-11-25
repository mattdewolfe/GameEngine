#include "Timer.h"

Timer::Timer()
{

}

void Timer::Start()
{

}

void Timer::Update()
{
	current = time(NULL);
}

bool Timer::Init()
{
	return true;
}

void Timer::Pause()
{

}

void Timer::Reset()
{

}

float Timer::GetDeltaTime()
{
	return static_cast<float>(time(NULL) - current);
}

Timer::~Timer()
{

}
