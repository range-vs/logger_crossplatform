#pragma once

#include "Logger.h"

#include <string>

/*
Использование: 
Сначала инициализировать логгер методом log_init, и передать в него имя приложения,его версию (можно и пустые строки кинуть) и
параметры инициализации (кроссплатформенные).
Далее вызывать один из четырёх методов, в зависимости от логирования:
- log_debug - сообщение;
- log_error - ошибка;
- log_critical_error - критическая ошибка с завершением приложения;
- log_warning - предупреждение.
и передать любое количество аргументов в функцию. Аргументы разделяются пробелом, и для вывода
должны перегружать operator<< (ostream).
Каждый метод возвращает false, если логгер не инициализирован, или true, если логгер готов к работе.
*/


class log
{
public:
	static void init(const std::string& nameGame, const std::string& versionGame, const LoggerParams& params);

	template<class ...Args >
	static bool debug(const char* file, const char* func, int line, Args... args);

	template<class ...Args >
	static bool error(const char* file, const char* func, int line, Args... args);

	template<class ...Args >
	static bool critical_error(const char* file, const char* func, int line, Args... args);

	template<class ...Args >
	static bool warning(const char* file, const char* func, int line, Args... args);
};


template<class ...Args>
bool log::debug(const char* file, const char* func, int line, Args... args)
{
	if (!Logger::getInstance()->isInit())
		return false;
	Logger::getInstance()->printToLog(LogType::LOG_MESSAGE, file, func, line, args...);
	return true;
}

template<class ...Args>
bool log::error(const char* file, const char* func, int line, Args... args)
{
	if (!Logger::getInstance()->isInit())
		return false;
	Logger::getInstance()->printToLog(LogType::LOG_ERROR, file, func, line, args...);
	return true;
}

template<class ...Args>
bool log::critical_error(const char* file, const char* func, int line, Args... args)
{
	if (!Logger::getInstance()->isInit())
		return false;
	Logger::getInstance()->printToLog(LogType::LOG_CRITICAL_ERROR, file, func, line, args...);
	return true;
}

template<class ...Args>
bool log::warning(const char* file, const char* func, int line, Args... args)
{
	if (!Logger::getInstance()->isInit())
		return false;
	Logger::getInstance()->printToLog(LogType::LOG_WARNING, file, func, line, args...);
	return true;
}

#ifndef NDEBUG
#define log_init(name, version, p) log::init(name, version, p)
#define log_debug(...) log::debug(__FILE__, __func__, __LINE__, __VA_ARGS__)
#define log_error(...) log::error(__FILE__, __func__, __LINE__, __VA_ARGS__)
#define log_critical_error(...) log::critical_error(__FILE__, __func__, __LINE__, __VA_ARGS__)
#define log_warning(...) log::warning(__FILE__, __func__, __LINE__, __VA_ARGS__)
#else
#define log_init(name, version, p)
#define log_debug(...) 
#define log_error(...) 
#define log_critical_error(...) 
#define log_warning(...) 
#endif