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