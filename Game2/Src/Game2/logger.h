/******************************************************************************/
/*!
\file		Logger.h
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	29/09/2923
\brief		Provides a logger class to manage log messages with different
            log levels.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/
#pragma once
#pragma warning(disable : 4251)
#pragma warning(disable : 4099)


#include "pch.h"
#include "Core.h"
#include <mutex>

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
        static Logger& GetInstance();

        // Delete copy constructor and assignment operator to prevent multiple instances
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        void Log(LogLevel level, const std::string& message);
        void Log(LogLevel level, const char* format, ...); // Use variadic arguments for formatted logging
        void Flush();


    private:
        Logger(const std::string& logFileName = "default_log.txt");
        ~Logger();

        void WriteLog(const std::string& logMessage);

        std::ofstream m_LogFile;
        std::mutex logMutex;  // Mutex for thread-safety
    };
}
