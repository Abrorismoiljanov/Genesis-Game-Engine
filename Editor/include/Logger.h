#pragma once
#include "string"
#include "vector"
#include <mutex>

enum class LogLevel {
    Info,
    Warning,
    Error
};
enum class LogSystem {
    Script,
    Physics,
    Renderer,
    Engine,
    Gameplay
};

struct LogEntry {
    std::string message;
    LogSystem system;
    LogLevel level;
};

class Logger {
public:
    void Info(LogSystem sys, const std::string& msg);

    void Warning(LogSystem sys, const std::string& msg);

    void Error(LogSystem sys, const std::string& msg);
 
    const char* LogSystemToString(LogSystem sys);
    std::vector<LogEntry> GetSnapshot() const;
    const std::vector<LogEntry>& Get() const;

private:
    static constexpr size_t MAX_LOGS = 1000;
    std::vector<LogEntry> logs;
    mutable std::mutex mutex;
};

