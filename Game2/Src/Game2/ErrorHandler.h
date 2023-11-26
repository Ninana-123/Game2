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
        /*!*********************************************************************
        \brief
        Sets up the default unhandled exception filter for the application.
         **************************************************************************/
        static void Initialize();

        /*!*********************************************************************
        \brief
        Translates exception codes into human - readable messages

        \param exceptionCode
        The exception code that was encountered.

        \return
        A string representing the human - readable message for the exception code.

         **************************************************************************/
        static std::string TranslateExceptionCode(DWORD exceptionCode);

    private:
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
        static LONG WINAPI ExceptionHandler(EXCEPTION_POINTERS* exceptionInfo);
    };

}