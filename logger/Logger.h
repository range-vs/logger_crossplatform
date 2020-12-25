#pragma once

#include <memory>
#include <tuple>
#include <fstream>
#include <functional>
#include <sstream>
#include <vector>

#include "helpers/tuple_utils.h"
#include "helpers/time_utils.h"
#include "messages/TypeMessages.h"

#include "output/BaseOutput.h"

class Logger;
using LoggerPtr = std::shared_ptr<Logger>;

class Logger
{
	static LoggerPtr instance;

	bool _init;
	std::vector<std::shared_ptr<BaseOutput>> allOutputs;

	Logger();

	struct WriterParamsToBufferCallback
	{
		std::stringstream& buffer;
		std::string delimeter;

		WriterParamsToBufferCallback(std::stringstream& buffer, const std::string& del);

		template<std::size_t Index, class T>
		void operator()(T&& element);
	};

protected:
	template<class ... Args>
	auto pack_to_tuple(Args... args);

	void release();

public:
	Logger(const Logger&) = delete;
	Logger(Logger&&) = delete;
	Logger& operator=(const Logger&) = delete;
	const Logger& operator=(Logger&&) = delete;
	static LoggerPtr getInstance();

	template<class ...Args>
	void printToLog(const LogType& id, const std::string& file, const std::string& func, int line, Args... args);

	void init(const std::string& nameGame, const std::string& versionGame, const LoggerParams& params);
	bool isInit()const noexcept;

	~Logger()
	{
		if(isInit())
			release();
	}
};


template<std::size_t Index, class T>
inline void Logger::WriterParamsToBufferCallback::operator()(T&& element)
{
	buffer << element << delimeter;
}

template<class ...Args>
inline auto Logger::pack_to_tuple(Args ...args)
{
	return std::make_tuple(std::forward<Args>(args)...);
}

template<class ...Args>
inline void Logger::printToLog(const LogType& id, const std::string & file, const std::string & func, int line, Args... args)
{
	std::stringstream buffer;
	buffer << "[" << TimeUtils::getCurrentTime() << "] File: " << file << ", function: " << func << ", line: " << line << ". Message: ";
	TupleHelper::foreachTuple(WriterParamsToBufferCallback(buffer, " "), pack_to_tuple(args...));
	buffer << std::endl;
	for (auto&& output : allOutputs)
		output->message(id, buffer.str());
	if(id == LogType::CRITICAL_ERROR)
	{
		_init = false;
		release();
		std::exit(-1);
	}
}