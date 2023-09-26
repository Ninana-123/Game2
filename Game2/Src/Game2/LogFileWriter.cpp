#include "pch.h"
#include "LogFileWriter.h"

namespace Engine {
    class LogFileWriterImpl {
    public:
        std::ofstream m_LogFile;
    };

    LogFileWriter::LogFileWriter(const std::string& filename)
        : pImpl(std::make_unique<LogFileWriterImpl>())
    {
        pImpl->m_LogFile.open(filename, std::ios::out | std::ios::trunc);  // Use trunc to clear the file if it exists
        if (!pImpl->m_LogFile.is_open()) {
            throw std::runtime_error("Failed to open log file.");
        }
    }


    LogFileWriter::~LogFileWriter() = default;

    void LogFileWriter::WriteLog(const std::string& logMessage) {
        if (pImpl->m_LogFile.is_open()) {
            pImpl->m_LogFile << logMessage << '\n';
            pImpl->m_LogFile.flush();
        }
    }
}
