#pragma once

#include <string>
#include "HTMLFileOutput.h"

#include "../helpers/time_utils.h"
#include <sstream>
#include <algorithm>
#include <regex>

#include "factory_messages/HTMLFactory.h"

//#ifdef ANDROID
//#include <AnalyticsWrapper/helpers/JNIHelper.h>
//#include "jni.h"
//#endif

std::string HTMLFileOutput::initStyles()
{
	/*
	Классы:
	row - строка таблицы базовый
	critical-error - строка таблицы критическая ошибка
	error - строка таблицы ошибка
	warning - строка таблицы предупреждение
	message - строка таблицы сообщение
	header - заголовок страницы
	panel-action - панель управления (чек боксы)
	table - таблица
	caption - заголовок таблицы
	*/
	return ".row{\
			  width: 100% ;\
			  font-size: 14pt;\
			  display: block;\
			  text-align: left\
			}\
			.critical-error{\
			  background-color:red;\
			}\
			.error{\
			  background-color:orange;\
			}\
			.warning{\
			  background-color:yellow;\
			}\
			.message{\
			  background-color:green;\
			}\
			.header{\
			  text-align: center;\
			}\
			.panel-action{\
			  margin-left: 3% ;\
			}\
			.table{\
				width: 100%\
			}\
			.caption{\
			  font-size: 19pt\
			}";
}

std::string HTMLFileOutput::initScript()
{
	return "function panel_action(){\
				var buttons = ['critical-error', 'error', 'warning', 'message'];\
				var classes = ['.critical-error', '.error', '.warning', '.message'];\
					for (var i = 0; i < buttons.length; ++i) {\
						var elems = document.querySelectorAll(classes[i]);\
						var style = 'none';\
						if (document.getElementById(buttons[i]).checked) {\
							style = 'block';\
						}\
						for (var j = 0; j < elems.length; j++) {\
							elems[j].style.display = style;\
						}\
				}\
			}";
}

void HTMLFileOutput::init(const std::string& nameGame, const std::string& versionGame)
{
	file.open("sdcard\Android\data\log.html");
	if (!file)
	{
		// TODO: throw exception
	}
	auto title("Log for session HGE engine");
	HTML::Document log;
	log.title(title);
	log.addAttribute("lang", "en");
	log.head() << /*HTML::Meta("utf-8") <<*/ HTML::Meta("viewport", "width=device-width, initial-scale=1, shrink-to-fit=no") << HTML::Style(HTMLFileOutput::initStyles());

	log.head() << HTML::Script(nullptr, HTMLFileOutput::initScript().c_str());

	log.body().cls("bg-light");
	// init common
	log.body() << HTML::Header2(title).addAttribute("class", "header");
	// init leftBar
	HTML::Div leftBar;
	leftBar << HTML::Header3("Время сессии: " + TimeUtils::getCurrentTime());
	leftBar << HTML::Header3("Наименование проекта: " + nameGame);
	leftBar << HTML::Header3("Версия проекта: " + versionGame) << HTML::Break() << HTML::Break();
	log.body() << std::move(leftBar);

	// инициализация панели управления
	HTML::Div panelAction;
	panelAction << HTML::Header3("Панель управления: ");
	panelAction << HTML::Input("checkbox").checked("true").id("critical-error").addAttribute("class", "panel-action").addAttribute("onclick", "panel_action()") << HTML::Text("Критические ошибки") << HTML::Break();
	panelAction << HTML::Input("checkbox").checked("true").id("error").addAttribute("class", "panel-action").addAttribute("onclick", "panel_action()") << HTML::Text("Ошибки") << HTML::Break();
	panelAction << HTML::Input("checkbox").checked("true").id("warning").addAttribute("class", "panel-action").addAttribute("onclick", "panel_action()") << HTML::Text("Предупреждения") << HTML::Break();
	panelAction << HTML::Input("checkbox").checked("true").id("message").addAttribute("class", "panel-action").addAttribute("onclick", "panel_action()") << HTML::Text("Сообщения") << HTML::Break();
	log.body() << std::move(panelAction);

	// инит таблицы
	HTML::Table table;
	table.addAttribute("class", "table") << HTML::Caption("Лог сообщений").addAttribute("class", "caption");
	log.body() << std::move(table);

	// получение окончания файла (для перезаписи)
	std::stringstream outPut;
	outPut << log;
	std::string text(outPut.str());
	// find END_HTML
	size_t index(text.find("</table>"));
	if (index == std::string::npos)
	{
		// TODO: throw exception
	}
	end_html = std::regex_replace(text.substr(index), std::regex("([\\s]*)"), "");
	text.resize(index);
	text += end_html;

	// запись в файл
	file << text;
	if(!file)
	{
		// TODO: throw exception
	}
	file.flush();
}

void HTMLFileOutput::message(const LogType& lt, const std::string & str)
{
	auto messageBuilder(CreatorMessagesHTMLFileOutput::create(lt));
	file.seekp(-static_cast<int>(sizeof(char) * (end_html.length())), std::ios::cur);
	if (!file)
	{
		// TODO: throw exception
	}
	file << messageBuilder->createTableLine(str) << end_html;
	if (!file)
	{
		// TODO: throw exception
	}
	file.flush();
}

HTMLFileOutput::~HTMLFileOutput()
{

}

