#pragma once

#include "BaseOutput.h"

#include "../../html/HTML.h"

class TerminalOutput: public BaseOutput
{

public:
	void init(const std::string& nameGame, const std::string& versionGame, const LoggerParams& params) override;
	void message(const LogType& lt, const std::string& str) override;
	~TerminalOutput()override;
};

