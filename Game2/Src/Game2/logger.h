#pragma once
#pragma warning(disable : 4251)

#include "pch.h"
#include "Core.h"
#include <fstream>


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
        Logger(const std::string& logFileName = "default_log.txt");
        ~Logger();

        void Log(LogLevel level, const std::string& message);

    private:
        void WriteLog(const std::string& logMessage);

        std::ofstream m_LogFile;
    };
    }