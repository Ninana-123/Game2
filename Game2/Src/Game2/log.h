#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Engine
{


}

//core log 
#define CORE_ERROR(...)  ::Engine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_WARN(...)   ::Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_TRACE(...)  ::Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...)   ::Engine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_FATAL(...)  ::Engine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//client log
#define CORE_ERROR(...)  ::Engine::Log::GetClientLogger()->error(__VA_ARGS__)
#define CORE_WARN(...)   ::Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CORE_TRACE(...)  ::Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...)   ::Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define CORE_FATAL(...)  ::Engine::Log::GetClientLogger()->fatal(__VA_ARGS__)

