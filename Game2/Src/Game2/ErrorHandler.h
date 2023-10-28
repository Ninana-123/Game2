// ErrorHandler.h

#include "Game2/logger.h"
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