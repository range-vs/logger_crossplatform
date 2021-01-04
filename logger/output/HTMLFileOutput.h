#pragma once

#include "BaseOutput.h"
#include <fstream>

#include "../../html/HTML.h"

class HTMLFileOutput: public BaseOutput
{
	static std::string initStyles();
	static std::string initScript();

	std::ofstream file;
	std::string end_html;

public:
	void init(const std::string& nameGame, const std::string& versionGame) override;
	void message(const LogType& lt, const std::string& str) override;
	~HTMLFileOutput()override;
};

