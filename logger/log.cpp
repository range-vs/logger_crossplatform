#include "log.h"

void log::init(const std::string & nameGame, const std::string & versionGame, const LoggerParams& params)
{
	Logger::getInstance()->init(nameGame, versionGame, params);
}
