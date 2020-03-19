#include "stdafx.h"
#include "GD19_App.h"
#include "GD_spdlog.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h" // must be included
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/stdout_sinks.h"

GD_spdlog::GD_spdlog()
{
	ConsoleActive = 0;
}


GD_spdlog::~GD_spdlog()
{
}

void GD_spdlog::Init()
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());

	ConsoleActive = 1;
	auto static console = spdlog::stdout_logger_mt("console");
}

void GD_spdlog::stdout_example(int Num,bool Kill)
{
	if (ConsoleActive == 0)
	{
		Init();
	}

	if (Kill == 1)
	{
		FreeConsole();
		ConsoleActive = 0;
		return;
	}

	freopen("CONOUT$", "w", stdout);
	spdlog::get("console")->info(Num); 

}
