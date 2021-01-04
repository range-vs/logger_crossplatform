#include "log.h"

void log::init(const std::string & nameGame, const std::string & versionGame)
{
	Logger::getInstance()->init(nameGame, versionGame);
}
