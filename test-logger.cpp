#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

#include "logger\log.h"

#include <boost/stacktrace.hpp>


int main()
{
	int a(546), b(34);
	auto arg(std::to_string(a) + std::to_string(b));

	log_init("test project", "0.0.1");

	log::debug("Скоты", "и геи", 4565);
	log_debug();
	log_debug("Любое сообщение", 564664);
	log_debug("ываывав");
	log_debug("Любое сообщение", 564664, 6465, "sadas");
	log_warning(arg);
	log_error("Критическая ошибка, описание оной");
	log_debug("Любое сообщение", 564664);
	log_error("Критическая ошибка, описание оной2");
	log_debug("Любое сообщение", 564664);
	//log_critical_error("Hello", 15, "my friend", 29.453, "!");
	log_warning("Hello", 15, 29.453, "!");

	std::stringstream stackTrace;
	stackTrace << boost::stacktrace::stacktrace();
	log_error("\n" + stackTrace.str());

	return 0;
}

// добавить вывод в wstring
// описать использование, и что юзаю либу для генерации html доков
// придумать передачу параметров для конкретных выводов логгера