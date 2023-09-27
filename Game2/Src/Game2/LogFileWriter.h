#pragma once

#include "Core.h"

namespace Engine {
    class GAME2_API LogFileWriterImpl;

    class GAME2_API LogFileWriter {
    public:
        LogFileWriter(const std::string& filename);
        ~LogFileWriter();

        void WriteLog(const std::string& logMessage);

    private:
        std::unique_ptr<LogFileWriterImpl> pImpl;
    };
}
