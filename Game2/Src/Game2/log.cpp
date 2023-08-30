// Log.cpp
#include "Log.h"

namespace Engine
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger; // Definition for s_CoreLogger
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger; // Definition for s_ClientLogger

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("GAME2");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("GAME3");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}


