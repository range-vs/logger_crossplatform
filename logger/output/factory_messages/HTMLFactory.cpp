#pragma once

#include "HTMLFactory.h"
#include <string>

#include <regex>

HTML::Row MessageHTMLFileOutput::createTableLine(const std::string& msg)
{
	HTML::Row row;
	auto msgNew(std::regex_replace(msg, std::regex("\n"), "<br>"));
	row.addAttribute("class", "row message") << HTML::ColHeader(msgNew);
	return row;
}

HTML::Row WarningHTMLFileOutput::createTableLine(const std::string& msg)
{
	HTML::Row row;
	auto msgNew(std::regex_replace(msg, std::regex("\n"), "<br>"));
	row.addAttribute("class", "row warning") << HTML::ColHeader(msgNew);
	return row;
}

HTML::Row ErrorHTMLFileOutput::createTableLine(const std::string& msg)
{
	HTML::Row row;
	auto msgNew(std::regex_replace(msg, std::regex("\n"), "<br>"));
	row.addAttribute("class", "row error") << HTML::ColHeader(msgNew);
	return row;
}

HTML::Row CriticalErrorHTMLFileOutput::createTableLine(const std::string& msg)
{
	HTML::Row row;
	auto msgNew(std::regex_replace(msg, std::regex("\n"), "<br>"));
	row.addAttribute("class", "row critical-error") << HTML::ColHeader(msgNew);
	return row;
}

std::map<LogType, std::shared_ptr<BaseMessageHTMLFileOutput>> CreatorMessagesHTMLFileOutput::messageCreators
(
	{
		{LogType::LOG_MESSAGE, std::make_shared<MessageHTMLFileOutput>()},
		{LogType::LOG_ERROR, std::make_shared<ErrorHTMLFileOutput>()},
		{LogType::LOG_WARNING, std::make_shared<WarningHTMLFileOutput>()},
		{LogType::LOG_CRITICAL_ERROR, std::make_shared<CriticalErrorHTMLFileOutput>()}
	}
);

std::shared_ptr<BaseMessageHTMLFileOutput>& CreatorMessagesHTMLFileOutput::create(const LogType & lt)
{
	return messageCreators[lt]; // TODO: потенциальное исключение
}