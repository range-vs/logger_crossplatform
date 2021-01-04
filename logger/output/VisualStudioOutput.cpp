#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#pragma once


#include "VisualStudioOutput.h"

#include <windows.h>

#include <string>
#include "../helpers/time_utils.h"
#include <sstream>
#include <algorithm>
#include <regex>
#include <iostream>

#include "factory_messages/TerminalFactory.h"

void VisualStudioOutput::init(const std::string& nameGame, const std::string& versionGame)
{
	// TODO: set russion local (in HGE engine)
	OutputDebugStringA("Log for session HGE engine\n");
	OutputDebugStringA(std::string("Время сессии: " + TimeUtils::getCurrentTime() + "\n").c_str());
	OutputDebugStringA(std::string("Наименование проекта: " + nameGame + "\n").c_str());
	OutputDebugStringA(std::string("Версия проекта: " + versionGame + "\n").c_str());
}

void VisualStudioOutput::message(const LogType& lt, const std::string & str)
{
	auto messageBuilder(CreatorMessagesTerminalOutput::create(lt));
	OutputDebugStringA(messageBuilder->createMessage(str).c_str());
}

VisualStudioOutput::~VisualStudioOutput()
{

}

#endif

