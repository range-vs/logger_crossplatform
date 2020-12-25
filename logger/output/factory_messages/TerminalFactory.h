#pragma once

#include <map>

#include "../../../html/HTML.h"
#include "../../messages/TypeMessages.h"

class BaseMessageTerminalOutput
{
public:
	virtual std::string createMessage(const std::string& msg) = 0;
};

class MessageTerminalOutput : public BaseMessageTerminalOutput
{
public:
	std::string createMessage(const std::string& msg) override;
};

class WarningTerminalOutput : public BaseMessageTerminalOutput
{
public:
	std::string createMessage(const std::string& msg) override;
};

class ErrorTerminalOutput : public BaseMessageTerminalOutput
{
public:
	std::string createMessage(const std::string& msg) override;
};

class CriticalErrorTerminalOutput : public BaseMessageTerminalOutput
{
public:
	std::string createMessage(const std::string& msg) override;
};

class CreatorMessagesTerminalOutput
{
	static std::map<LogType, std::shared_ptr<BaseMessageTerminalOutput>> messageCreators;

public:
	static std::shared_ptr<BaseMessageTerminalOutput>& create(const LogType& lt);
};

