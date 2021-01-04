#include "Logger.h"

#include "output/HTMLFileOutput.h"
#include "output/TerminalOutput.h"
#ifdef _WIN32
#include "output/VisualStudioOutput.h"
#endif

LoggerPtr Logger::instance(nullptr);

Logger::Logger()
:_init(false)
{
}

LoggerPtr Logger::getInstance()
{
	if (!instance)
	{
		instance.reset(new Logger);
		if (!instance)
		{
			// TODO: throw exception
		}
	}
	return instance;
}

void Logger::init(const std::string& nameGame, const std::string& versionGame)
{
	_init = true;
	allOutputs.emplace_back(std::make_shared<HTMLFileOutput>());
	allOutputs.emplace_back(std::make_shared<TerminalOutput>());
#ifdef _WIN32
	allOutputs.emplace_back(std::make_shared<VisualStudioOutput>());
#endif

	for (auto&& output : allOutputs)
		output->init(nameGame, versionGame);
}

void Logger::release()
{
	
}

bool Logger::isInit()const noexcept
{
	return _init;
}

Logger::WriterParamsToBufferCallback::WriterParamsToBufferCallback(std::stringstream & buffer, const std::string& del)
: buffer(buffer),
delimeter(del)
{
}

