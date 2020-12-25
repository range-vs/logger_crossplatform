#pragma once

#include <string>
#include "../helpers/LoggerParams.h"
#include "../messages/TypeMessages.h"

class BaseOutput
{
public:
	virtual void init(const std::string& nameGame, const std::string& versionGame, const LoggerParams& params) = 0;
	virtual void message(const LogType& lt, const std::string& str) = 0;
	virtual ~BaseOutput() {};
};