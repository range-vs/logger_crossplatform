#pragma once

#include <map>

#include "../../../html/HTML.h"
#include "../../messages/TypeMessages.h"

class BaseMessageHTMLFileOutput
{
public:
	virtual HTML::Row createTableLine(const std::string& msg) = 0;
};

class MessageHTMLFileOutput : public BaseMessageHTMLFileOutput
{
public:
	HTML::Row createTableLine(const std::string& msg) override;
};

class WarningHTMLFileOutput : public BaseMessageHTMLFileOutput
{
public:
	HTML::Row createTableLine(const std::string& msg) override;
};

class ErrorHTMLFileOutput : public BaseMessageHTMLFileOutput
{
public:
	HTML::Row createTableLine(const std::string& msg) override;
};

class CriticalErrorHTMLFileOutput : public BaseMessageHTMLFileOutput
{
public:
	HTML::Row createTableLine(const std::string& msg) override;
};

class CreatorMessagesHTMLFileOutput
{
	static std::map<LogType, std::shared_ptr<BaseMessageHTMLFileOutput>> messageCreators;

public:
	static std::shared_ptr<BaseMessageHTMLFileOutput>& create(const LogType& lt);
};
