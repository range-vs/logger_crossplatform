#pragma once

#include "HTMLFactory.h"
#include <string>

HTML::Row MessageHTMLFileOutput::createTableLine(const std::string& msg)
{
	HTML::Row row;
	row.addAttribute("class", "row message") << HTML::ColHeader(msg);
	return row;
}

HTML::Row WarningHTMLFileOutput::createTableLine(const std::string& msg)
{
	HTML::Row row;
	row.addAttribute("class", "row warning") << HTML::ColHeader(msg);
	return row;
}

HTML::Row ErrorHTMLFileOutput::createTableLine(const std::string& msg)
{
	HTML::Row row;
	row.addAttribute("class", "row error") << HTML::ColHeader(msg);
	return row;
}

HTML::Row CriticalErrorHTMLFileOutput::createTableLine(const std::string& msg)
{
	HTML::Row row;
	row.addAttribute("class", "row critical-error") << HTML::ColHeader(msg);
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