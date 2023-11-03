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
    /*!*********************************************************************
        \brief
        Sets up the default unhandled exception filter for the application.
     **************************************************************************/
    void ErrorHandler::Initialize() {
        SetUnhandledExceptionFilter(ExceptionHandler);
    }
    /*!*********************************************************************
        \brief
        Custom exception handler that logs unhandled exceptions.

        \param exceptionInfo
        A pointer to an EXCEPTION_POINTERS structure that contains information
        about the exception and the state of the processor at the time of the
        exception.

        \return
        A status code.EXCEPTION_EXECUTE_HANDLER if successful, or an appropriate
        error status code.

      *************************************************************************/
    LONG WINAPI ErrorHandler::ExceptionHandler(EXCEPTION_POINTERS* exceptionInfo) {
        DWORD exceptionCode = exceptionInfo->ExceptionRecord->ExceptionCode;

        std::string errorMessage = "Unhandled exception: " + TranslateExceptionCode(exceptionCode);
        Logger::GetInstance().Log(LogLevel::Error, errorMessage);
        return EXCEPTION_EXECUTE_HANDLER;
    }
    /*!*********************************************************************
        \brief
        Translates exception codes into human - readable messages

        \param exceptionCode
        The exception code that was encountered.

        \return
        A string representing the human - readable message for the exception code.

     **************************************************************************/
    std::string ErrorHandler::TranslateExceptionCode(DWORD exceptionCode) {
        switch (exceptionCode) {
        case EXCEPTION_ACCESS_VIOLATION:         return "Access violation";
        case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:    return "Array bounds exceeded";
        case EXCEPTION_BREAKPOINT:               return "Breakpoint";
        default:                                 return "Unknown exception";
        }
    }

}