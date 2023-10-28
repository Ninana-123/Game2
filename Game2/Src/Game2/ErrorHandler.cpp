#include "pch.h"
#include "ErrorHandler.h"
#include "logger.h"

namespace Engine {

    void ErrorHandler::Initialize() {
        SetUnhandledExceptionFilter(ExceptionHandler);
    }

    LONG WINAPI ErrorHandler::ExceptionHandler(EXCEPTION_POINTERS* exceptionInfo) {
        DWORD exceptionCode = exceptionInfo->ExceptionRecord->ExceptionCode;

        std::string errorMessage = "Unhandled exception: " + TranslateExceptionCode(exceptionCode);
        Logger::GetInstance().Log(LogLevel::Error, errorMessage);
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