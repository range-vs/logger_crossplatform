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
		{LogType::MESSAGE, std::make_shared<MessageHTMLFileOutput>()},
		{LogType::ERROR, std::make_shared<ErrorHTMLFileOutput>()},
		{LogType::WARNING, std::make_shared<WarningHTMLFileOutput>()},
		{LogType::CRITICAL_ERROR, std::make_shared<CriticalErrorHTMLFileOutput>()}
	}
);

std::shared_ptr<BaseMessageHTMLFileOutput>& CreatorMessagesHTMLFileOutput::create(const LogType & lt)
{
	return messageCreators[lt]; // TODO: потенциальное исключение
}