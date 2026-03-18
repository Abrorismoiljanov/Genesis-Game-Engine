#include "Editor/include/Logger.h"


void Logger::Info(LogSystem sys, const std::string& msg) {
    std::lock_guard<std::mutex> lock(mutex);
    if (logs.size() >= MAX_LOGS) logs.erase(logs.begin());
    logs.push_back({ msg, sys, LogLevel::Info });
}

void Logger::Warning(LogSystem sys, const std::string& msg) {
    std::lock_guard<std::mutex> lock(mutex);
    if (logs.size() >= MAX_LOGS) logs.erase(logs.begin());
    logs.push_back({ msg, sys, LogLevel::Warning });
}


void Logger::Error(LogSystem sys, const std::string& msg) {
    std::lock_guard<std::mutex> lock(mutex);
    if (logs.size() >= MAX_LOGS) logs.erase(logs.begin());
    logs.push_back({ msg, sys, LogLevel::Error });
}

std::vector<LogEntry> Logger::GetSnapshot() const {
    std::lock_guard<std::mutex> lock(mutex);
    return logs; // safe copy for UI
}

const char* Logger::LogSystemToString(LogSystem sys) {
    switch(sys) {
        case LogSystem::Script: return "Script";
        case LogSystem::Physics: return "Physics";
        case LogSystem::Renderer: return "Renderer";
        case LogSystem::Engine: return "Engine";
        case LogSystem::Gameplay: return "Gameplay";
    }
    return "Unknown";
}
const std::vector<LogEntry>& Logger::Get() const {
    return logs; 
}
