#pragma once

#include <string>
#include <chrono>
#include <ctime>
#include <time.h>

class TimeUtils
{
	enum {SIZE_TIME_BUFFER = 512};
public:
	static std::string getCurrentTime()
	{
		std::time_t time(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
#ifdef ANDROID
		char *timeStr(ctime(&time));
		return std::string(timeStr, strlen(timeStr) - 1);
#else
		char timeStr[SIZE_TIME_BUFFER];
		ctime_s(timeStr, sizeof(timeStr), &time);
		return std::string(timeStr, strlen(timeStr) - 1);
#endif
	}
};