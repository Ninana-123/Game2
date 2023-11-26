/******************************************************************************/
/*!
\file		Logger.cpp
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	29/09/2923
\brief		Implementation of the Logger class for managing log messages
            with different log levels.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "pch.h"
#include "logger.h"


namespace Engine {

    // Static instance for singleton pattern
    Logger& Logger::GetInstance() {
        static Logger instance; // Guaranteed to be destroyed and instantiated on first use
        return instance;
    }

    void Logger::Log(LogLevel level, const std::string& message) {
        try {
            Log(level, message.c_str()); // delegate to the const char* version
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    Logger::Logger(const std::string& logFileName) {
        try {
            // Ensure the directory exists
            std::filesystem::create_directories("Resource/Logs/");

            std::string fullPath = "Resource/Logs/" + logFileName;
            m_LogFile.open(fullPath, std::ios::out | std::ios::trunc);
            if (!m_LogFile.is_open()) {
                throw std::runtime_error("Failed to open log file.");
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    Logger::~Logger() {
        try {
            if (m_LogFile.is_open()) {
                m_LogFile.flush(); // Flush any buffered content
                m_LogFile.close();
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }


    void Logger::Log(LogLevel level, const char* format, ...) {
        try {
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
            default:
                throw std::invalid_argument("Unknown log level");
            }

            std::time_t now = std::time(nullptr);
            struct tm timeInfo;
            localtime_s(&timeInfo, &now);

            char timestamp[64];
            std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &timeInfo);

            char logContent[512]; // Adjust size if needed
            va_list args;
            va_start(args, format);
            vsnprintf(logContent, sizeof(logContent), format, args);
            va_end(args);

            std::string logEntry = std::string(timestamp) + " " + levelStr + " " + logContent;
            std::cout << logEntry << std::endl;

            std::lock_guard<std::mutex> lock(logMutex); // Ensure thread safety when writing
            WriteLog(logEntry);
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void Logger::WriteLog(const std::string& logMessage) {
        try {
            if (m_LogFile.is_open()) {
                m_LogFile << logMessage << '\n';
                if (!m_LogFile.good()) {
                    throw std::runtime_error("Failed to write to log file.");
                }
                m_LogFile.flush();
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    void Logger::Flush() {
        try {
            if (m_LogFile.is_open()) {
                m_LogFile.flush();
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

}
