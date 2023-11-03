/******************************************************************************/
/*!
\file		ErrorHandler.h
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	01/11/2923
\brief		This file contains the declaration of ErrorHandler Class
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once

#include "logger.h"
#include <Windows.h>
#include <string>

namespace Engine {

    class GAME2_API ErrorHandler {
    public:
        // Initialize the error handler
        static void Initialize();

        // Translates the exception code to a string description
        static std::string TranslateExceptionCode(DWORD exceptionCode);

    private:
        // The actual exception handler function
        static LONG WINAPI ExceptionHandler(EXCEPTION_POINTERS* exceptionInfo);
    };

}