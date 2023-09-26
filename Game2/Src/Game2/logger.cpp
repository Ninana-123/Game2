#include "pch.h"
#include "Game2/logger.h"


namespace Engine {
    void Logger::LogInternal(LogLevel level, const std::string& message) {
        std::string levelStr;
        switch (level) {
        case LogLevel::Debug:
            levelStr = "[DEBUG]";
            break;
        case LogLevel::App:
            levelStr = "[APP]";
            break;
        case LogLevel::Event:
            levelStr = "[EVENT]";
            break;
        case LogLevel::Info:
            levelStr = "[INFO]";
            break;
        case LogLevel::Error:
            levelStr = "[ERROR]";
            break;
        }

        std::time_t now = std::time(nullptr);
        struct tm timeInfo;
        localtime_s(&timeInfo, &now); 

        char timestamp[64];
        std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &timeInfo);

        std::string logEntry = timestamp + levelStr + " " + message;
        std::cout << logEntry << std::endl;
    }
}
