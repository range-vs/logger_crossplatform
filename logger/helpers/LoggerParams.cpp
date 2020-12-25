//
// Created by range on 24.12.2020.
//

#include "LoggerParams.h"

void LoggerParams::setPathToFile(const std::string& path) noexcept
{
    this->pathToFile = path;
}

const std::string& LoggerParams::getPathToFile() const noexcept
{
    return this->pathToFile;
}
