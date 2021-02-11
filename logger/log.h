#pragma once

#include "Logger.h"

#include <string>

/*
Использование: 
Сначала инициализировать логгер методом log_init, и передать в него имя приложения,его версию (можно и пустые строки кинуть).
Далее вызывать один из четырёх методов, в зависимости от логирования:
- log_debug - сообщение;
- log_error - ошибка;
- log_critical_error - критическая ошибка с завершением приложения;
- log_warning - предупреждение.
и передать любое количество аргументов в функцию. Аргументы разделяются пробелом, и для вывода
должны перегружать operator<< (ostream).
Каждый метод возвращает false, если логгер не инициализирован, или true, если логгер готов к работе.
*/

#ifndef NDEBUG

class log
{
public:
	static void init(const std::string& nameGame, const std::string& versionGame);
	
	template<class ...Args >
	static bool debug(Args... args);

	template<class ...Args >
	static bool error(Args... args);

	template<class ...Args >
	static bool critical_error(Args... args);

	template<class ...Args >
	static bool warning(Args... args);
};


template<class ...Args>
bool log::debug(Args... args)
{
	if (!Logger::getInstance()->isInit())
		return false;
	Logger::getInstance()->printToLog(LogType::LOG_MESSAGE, args...);
	return true;
}

template<class ...Args>
bool log::error(Args... args)
{
	if (!Logger::getInstance()->isInit())
		return false;
	Logger::getInstance()->printToLog(LogType::LOG_ERROR, args...);
	return true;
}

template<class ...Args>
bool log::critical_error(Args... args)
{
	if (!Logger::getInstance()->isInit())
		return false;
	Logger::getInstance()->printToLog(LogType::LOG_CRITICAL_ERROR, args...);
	return true;
}

template<class ...Args>
bool log::warning(Args... args)
{
	if (!Logger::getInstance()->isInit())
		return false;
	Logger::getInstance()->printToLog(LogType::LOG_WARNING, args...);
	return true;
}

#define log_init(name, version) log::init(name, version)
#define log_debug(...) log::debug(std::string("File: ") + __FILE__, std::string(", function: ") + __func__, ", line: " + std::to_string(__LINE__), ". Message: ", __VA_ARGS__)
#define log_error(...) log::error(std::string("File: ") + __FILE__, std::string(", function: ") + __func__, ", line: " + std::to_string(__LINE__), ". Message: ", __VA_ARGS__)
#define log_critical_error(...) log::critical_error(std::string("File: ") + __FILE__, std::string(", function: ") + __func__, ", line: " + std::to_string(__LINE__), ". Message: ", __VA_ARGS__)
#define log_warning(...) log::warning(std::string("File: ") + __FILE__, std::string(", function: ") + __func__, ", line: " + std::to_string(__LINE__), ". Message: ", __VA_ARGS__)
#else
class log
{
public:
	static void init(const std::string& nameGame, const std::string& versionGame){}

	template<class ...Args >
	static bool debug(Args... args) { return true; }

	template<class ...Args >
	static bool error(Args... args) { return true; }

	template<class ...Args >
	static bool critical_error(Args... args) { return true; }

	template<class ...Args >
	static bool warning(Args... args) { return true; }
};

#define log_init(name, version)
#define log_debug(...) 
#define log_error(...) 
#define log_critical_error(...) 
#define log_warning(...) 
#endif