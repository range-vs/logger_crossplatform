//
// Created by range on 24.12.2020.
//

#pragma once

#include <string>

class LoggerParams
{
    std::string pathToFile;
public:
    void setPathToFile(const std::string& path) noexcept;
    const std::string& getPathToFile()const noexcept;

};


