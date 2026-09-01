//
// Created by Nemesis Verstraete on 24/07/2026.
//
#pragma once
#include <iostream>
#include <string_view>
#include <sstream>
#include <stdexcept>

namespace obsidium {

enum class LogLevel {
    Info,
    Warning,
    Error,
    Fatal
};

#define LOG_INFO(...) ::obsidium::Logger::Log(::obsidium::LogLevel::Info, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARNING(...) ::obsidium::Logger::Log(::obsidium::LogLevel::Warning, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) ::obsidium::Logger::Log(::obsidium::LogLevel::Error, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) ::obsidium::Logger::Log(::obsidium::LogLevel::Fatal, __FILE__, __LINE__, __VA_ARGS__)

constexpr std::string_view LogLevelToString(const LogLevel level) {
    switch (level) {
        case LogLevel::Info: return "info";
        case LogLevel::Warning: return "warning";
        case LogLevel::Error: return "error";
        case LogLevel::Fatal: return "fatal";
        default: return "unknown";
    }
}

class Logger {
public:
    static Logger& getInstance() {
        static Logger logger;
        return logger;
    };

    template<typename... Args>
    static void Log(const LogLevel level, std::string_view file, const uint32_t line, Args... args) {
        std::stringstream ss;
        ss << "[" << LogLevelToString(level) << "] [" << file << ":" << line << "] ";

        ((ss << std::forward<Args>(args) << " "), ...);

        if (level == LogLevel::Fatal) {
            throw std::runtime_error(ss.str());
        }

        std::cout << ss.str() << std::endl;
    }
};

}