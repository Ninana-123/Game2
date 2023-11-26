/******************************************************************************/
/*!
\file		ErrorHandler.cpp
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	01/11/2923
\brief		This file contains the definition of ErrorHandler Class
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "pch.h"
#include "ErrorHandler.h"
#include "logger.h"

namespace Engine {

    void ErrorHandler::Initialize() {
        SetUnhandledExceptionFilter(ExceptionHandler);
    }

    LONG WINAPI ErrorHandler::ExceptionHandler(EXCEPTION_POINTERS* exceptionInfo) {
        DWORD exceptionCode = exceptionInfo->ExceptionRecord->ExceptionCode;

        // Construct error message
        std::string errorMessage = "Unhandled exception: " + TranslateExceptionCode(exceptionCode);

        // Log the error message
        Logger::GetInstance().Log(LogLevel::Error, errorMessage);

        // Indicate that the exception has been handled
        return EXCEPTION_EXECUTE_HANDLER;
    }

    std::string ErrorHandler::TranslateExceptionCode(DWORD exceptionCode) {
        switch (exceptionCode) {
        case EXCEPTION_ACCESS_VIOLATION:         return "Access violation";
        case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:    return "Array bounds exceeded";
        case EXCEPTION_BREAKPOINT:               return "Breakpoint";
        default:                                 return "Unknown exception";
        }
    }
}