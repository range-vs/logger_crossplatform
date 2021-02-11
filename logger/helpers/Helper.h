#pragma once

#include <sstream>
#include <string>
#include <vector>

class Helper
{
public:
    static std::vector<std::string> doSegmentByCharacter(const std::string& sentence, char symbol = '\n')
    {
        std::vector<std::string> buf;
        std::stringstream ss(sentence);
        std::string to;

        if (!sentence.empty())
            while (std::getline(ss, to, symbol))
                buf.emplace_back(to);
        return buf;
    }
};