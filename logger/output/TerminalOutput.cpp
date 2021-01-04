#pragma once

#include <string>
#include "TerminalOutput.h"

#include "../helpers/time_utils.h"
#include <sstream>
#include <algorithm>
#include <regex>
#include <iostream>

#include "factory_messages/TerminalFactory.h"

void TerminalOutput::init(const std::string& nameGame, const std::string& versionGame)
{
	// TODO: set russion local (in HGE engine)
	std::cout << "Log for session HGE engine" << std::endl;
	std::cout << "Время сессии: " + TimeUtils::getCurrentTime() << std::endl;
	std::cout << "Наименование проекта: " << nameGame << std::endl;
	std::cout << "Версия проекта: " + versionGame << std::endl;
}

void TerminalOutput::message(const LogType& lt, const std::string & str)
{
	auto messageBuilder(CreatorMessagesTerminalOutput::create(lt));
	std::cout << messageBuilder->createMessage(str);
}

TerminalOutput::~TerminalOutput()
{

}

