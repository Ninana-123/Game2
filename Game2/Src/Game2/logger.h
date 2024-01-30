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
#ifndef ENGINE_LOGGER_H
#define ENGINE_LOGGER_H

#pragma warning(disable : 4251)
#pragma warning(disable : 4099)

#include "pch.h"
#include "Core.h"
#include <mutex>

namespace Engine {
    /*!
    * \brief Enumeration representing different log levels.
    *
    * The LogLevel enum class defines different log levels, including Debug, App, Event, Info, and Error.
    */
    enum class LogLevel {
        Debug,
        App,
        Event,
        Info,
        Error
    };

    class GAME2_API Logger {
    public:
        /*!
        * \brief Get the singleton instance of the Logger class.
        * \return Logger& Reference to the Logger instance.
        */
        static Logger& GetInstance();

        // Delete copy constructor and assignment operator to prevent multiple instances
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        /*!
         * \brief Log a message with the specified log level.
         * \param level The log level (Debug, App, Event, Info, Error).
         * \param message The log message.
         */
        void Log(LogLevel level, const std::string& message);

        /*!
         * \brief Log a formatted message with the specified log level.
         * \param level The log level (Debug, App, Event, Info, Error).
         * \param format The format string for the log message.
         * \param ... Variadic arguments for formatted logging.
         */
        void Log(LogLevel level, const char* format, ...); // Use variadic arguments for formatted logging

        /*!
         * \brief Flush the log file.
         */
        void Flush();

    private:
        /*!
         * \brief Constructor for the Logger class.
         * \param logFileName The name of the log file.
         */
        Logger(const std::string& logFileName = "default_log.txt");

        /*!
         * \brief Destructor for the Logger class.
         */
        ~Logger();

        /*!
         * \brief Write a log message to the log file.
         * \param logMessage The log message to write.
         */
        void WriteLog(const std::string& logMessage);

        std::ofstream m_LogFile;
        std::mutex logMutex;  // Mutex for thread-safety
    };
}
#endif ENGINE_LOGGER_H