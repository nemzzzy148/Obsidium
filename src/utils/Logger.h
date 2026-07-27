//
// Created by Nemesis Verstraete on 24/07/2026.
//
#pragma once
#include <iostream>
#include <string_view>

namespace obsidium {

enum class LogLevel {
    Info,
    Warning,
    Error,
    Fatal
};

inline std::string_view LogLevelToString(const LogLevel level) {
    switch (level) {
        case LogLevel::Info: return "INFO: ";
        case LogLevel::Warning: return "WARNING:";
        case LogLevel::Error: return "ERROR:";
        case LogLevel::Fatal: return "FATAL: ";
        default: return "UNKNOWN: ";
    }
}

class Logger {
    static Logger& getInstance() {
        static Logger logger;
        return logger;
    };

    template<typename... Args>
    static void Log(const LogLevel level, Args... args) {
        std::cout << LogLevelToString(level);
        (std::cout << ... << args) << std::endl;
    }
};

}
