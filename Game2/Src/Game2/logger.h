#pragma once

#include "pch.h"
#include "Core.h"
#include <string>

namespace Engine {
    enum class LogLevel {
        Debug,
        App,
        Event,
        Info,
        Error
    };

    class GAME2_API Logger {
    public:
        // Make Log function conditional on whether NDEBUG is defined
        void Log(LogLevel level, const std::string& message) {
#ifdef NDEBUG
            // In release mode, log messages will not be displayed
#else
            // In debug mode, log messages will be displayed
            LogInternal(level, message);
#endif
        }

    private:
        void LogInternal(LogLevel level, const std::string& message);
    };
}
