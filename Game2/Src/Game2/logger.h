    #pragma once

#include "pch.h"
#include "Core.h"
#include "LogFileWriter.h"

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
        Logger() : m_FileWriter("default_log.txt") {}
        Logger(const std::string& logFileName);
        ~Logger();
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
        LogFileWriter m_FileWriter;
    };
}
