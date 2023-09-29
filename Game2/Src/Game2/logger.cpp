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
#include "Game2/logger.h"


namespace Engine {
    /*!**********************************************************************
    \brief
    Constructor for the Logger class.
    \param[in] logFileName 
    The name of the log file to be opened.
    *************************************************************************/
    Logger::Logger(const std::string& logFileName) {
        m_LogFile.open(logFileName, std::ios::out | std::ios::trunc);
        if (!m_LogFile.is_open()) {
            throw std::runtime_error("Failed to open log file.");
        }
    }
    /*!**********************************************************************
    \brief
    Destructor for the Logger class.
    *************************************************************************/
    Logger::~Logger() {
        if (m_LogFile.is_open()) {
            m_LogFile.close();
        }
    }
    /*!**********************************************************************
    \brief
    Logs a message with the specified log level.
    \param[in] level 
    The log level of the message.
    \param[in] message
    The message to be logged.
    *************************************************************************/
    void Engine::Logger::Log(LogLevel level, const std::string& message) {
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
        WriteLog(logEntry);
    }
    /*!**********************************************************************
    \brief
    Writes a log message to the log file.
    \param[in] logMessage 
    The message to be written to the log file.
    *************************************************************************/
    void Logger::WriteLog(const std::string& logMessage) {
        if (m_LogFile.is_open()) {
            m_LogFile << logMessage << '\n';
            m_LogFile.flush();
        }
    }
}
