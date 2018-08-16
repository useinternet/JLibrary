#pragma once
#include<chrono>
class JTimer
{
	static std::chrono::system_clock::time_point totalTime;
	static std::chrono::system_clock::time_point stopTime;
	static std::chrono::system_clock::time_point start;
	static std::chrono::system_clock::time_point end;
	static float m_DeltaTime;
	static bool  bStop;
public:
	static float GetDeltaTime();
	static void  Stop();
	static void  Start();
};

class JStopWatch
{
	std::chrono::system_clock::time_point time;
	bool  bEnd;
public:
	void  Start(const float goalTime);
	void  Stop();
	bool  Update();
	bool  End();
};