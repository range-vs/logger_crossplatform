#pragma once

#include "TerminalFactory.h"
#include <string>


std::string MessageTerminalOutput::createMessage(const std::string& msg)
{
	return "DEBUG MESSAGE: " + msg;
}

std::string WarningTerminalOutput::createMessage(const std::string& msg)
{
	return "WARNING: " + msg;
}

std::string ErrorTerminalOutput::createMessage(const std::string& msg)
{
	return "ERROR: " + msg;
}

std::string CriticalErrorTerminalOutput::createMessage(const std::string& msg)
{
	return "CRITICAL ERROR: " + msg;
}

std::map<LogType, std::shared_ptr<BaseMessageTerminalOutput>> CreatorMessagesTerminalOutput::messageCreators
(
	{
		{LogType::LOG_MESSAGE, std::make_shared<MessageTerminalOutput>()},
		{LogType::LOG_ERROR, std::make_shared<ErrorTerminalOutput>()},
		{LogType::LOG_WARNING, std::make_shared<WarningTerminalOutput>()},
		{LogType::LOG_CRITICAL_ERROR, std::make_shared<CriticalErrorTerminalOutput>()}
	}
);

std::shared_ptr<BaseMessageTerminalOutput>& CreatorMessagesTerminalOutput::create(const LogType & lt)
{
	return messageCreators[lt]; // TODO: потенциальное исключение
}
