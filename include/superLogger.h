#include "Arduino.h"

class Debug
{
public:
    enum LogLevel
    {
        NONE,
        ERROR,
        WARNING,
        INFO,
        DEBUG,
        VERBOSE
    };

    Debug(const String &name, LogLevel level = NONE, bool pName = true, bool pLvl = true,bool pAnsi = true,  bool pLoc = true) : name_(name), level_(level),printName_(pName),printLevel_(pLvl), printAnsi_(pAnsi), printLocation_(pLoc) {}

    void setName(const String &name)
    {
        name_ = name;
    }

    void setLevel(LogLevel level)
    {
        level_ = level;
    }

    void printName(bool set)
    {
        printName_ = set;
    }

    void printColor(bool set)
    {
        printAnsi_ = set;
    }

    void printLevel(bool set)
    {
        printLevel_ = set;
    }
    void printLocation(bool set)
    {
        printLocation_ = set;
    }

    template <typename... Args>

    void error(const char *funcName, const char *fileName, int lineNumber, const char *format, Args... args)
    {
        if (level_ >= ERROR)
        {
            String outputString = formatString(format, args...);
            logError(outputString, funcName, fileName, lineNumber);
        }
    }

    template <typename... Args>
    void warning(const char *funcName, const char *fileName, int lineNumber, const char *format, Args... args)
    {
        if (level_ >= WARNING)
        {
            String outputString = formatString(format, args...);
            logWarning(outputString, funcName, fileName, lineNumber);
        }
    }

    template <typename... Args>
    void info(const char *funcName, const char *fileName, int lineNumber, const char *format, Args... args)
    {
        if (level_ >= INFO)
        {
            String outputString = formatString(format, args...);
            logInfo(outputString, funcName, fileName, lineNumber);
        }
    }

    template <typename... Args>
    void debug(const char *funcName, const char *fileName, int lineNumber, const char *format, Args... args)
    {
        if (level_ >= DEBUG)
        {
            String outputString = formatString(format, args...);
            logDebug(outputString, funcName, fileName, lineNumber);
        }
    }

    template <typename... Args>
    void verbose(const char *funcName, const char *fileName, int lineNumber, const char *format, Args... args)
    {
        if (level_ >= VERBOSE)
        {
            String outputString = formatString(format, args...);
            logVerbose(outputString, funcName, fileName, lineNumber);
        }
    }

    template <typename... Args>
    String formatString(const char *format, Args... args)
    {
        char buffer[512];
        snprintf(buffer, sizeof(buffer), format, args...);
        return String(buffer);
    }

private:
    String name_;
    LogLevel level_;
    bool printName_;
    bool printLevel_;
    bool printAnsi_;
    bool printLocation_;

    void logError(const String &message, const char *funcName, const char *fileName, int lineNumber)
    {
            Serial.printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
        (printAnsi_ ? "\033[91m" : ""),   // ANSI color for red
        (printName_ ? "[" : ""),      // File location (if enabled)
        (printName_ ? name_.c_str() : ""),       // name (if enabled)
        (printName_ ? "]" : ""),      // File location (if enabled)
        (printLevel_ ? "[E]" : ""),       // Log level (if enabled)
        (printLocation_ ? "[" : ""),      // File location (if enabled)
        (printLocation_ ? fileName : ""), // File name (if enabled)
        (printLocation_ ? ":" : ""),      // File location (if enabled)
        (printLocation_ ? String(lineNumber).c_str() : ""), // Line number (if enabled)
        (printLocation_ ? "] " : ""),      // File location (if enabled)
        (printLocation_ ? funcName : ""),      // Function name (if enabled)
        (printLocation_ ? "(): " : ""),      // File location (if enabled)
        message.c_str(),                  // Log message
        (printAnsi_ ? "\033[0m" : "")     // Reset ANSI color
    );
        // Serial.printf("\033[31m[%s][E][%s:%d]%s(): %s\033[0m\n", name_.c_str(), fileName, lineNumber, funcName, message.c_str());
        // char location[128];
        // sprintf(location,"[%s:%d]%s(): ",fileName, lineNumber, funcName);
        // Serial.printf("%s[%s]%s%s%s%s\n", (printAnsi_ ? "\033[91m" : ""), name_.c_str(),(printLevel_ ? "[E]" : ""),(printLocation_?location:""), message.c_str(), (printAnsi_ ? "\033[0m" : ""));
        // Serial.printf("%s[%s]%s [%s:%d]%s(): %s%s\n", (printAnsi_ ? "\033[91m" : ""), name_.c_str(),(printLevel_ ? "[E]" : ""), fileName, lineNumber, funcName, message.c_str(), (printAnsi_ ? "\033[0m" : ""));
    }

    void logWarning(const String &message, const char *funcName, const char *fileName, int lineNumber)
    {
                    Serial.printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
        (printAnsi_ ? "\033[33m" : ""),   // ANSI color for red
        (printName_ ? "[" : ""),      // File location (if enabled)
        (printName_ ? name_.c_str() : ""),       // name (if enabled)
        (printName_ ? "]" : ""),      // File location (if enabled)
        (printLevel_ ? "[E]" : ""),       // Log level (if enabled)
        (printLocation_ ? "[" : ""),      // File location (if enabled)
        (printLocation_ ? fileName : ""), // File name (if enabled)
        (printLocation_ ? ":" : ""),      // File location (if enabled)
        (printLocation_ ? String(lineNumber).c_str() : ""), // Line number (if enabled)
        (printLocation_ ? "] " : ""),      // File location (if enabled)
        (printLocation_ ? funcName : ""),      // Function name (if enabled)
        (printLocation_ ? "(): " : ""),      // File location (if enabled)
        message.c_str(),                  // Log message
        (printAnsi_ ? "\033[0m" : "")     // Reset ANSI color
    );
        // Serial.printf("%s[%s][W][%s:%d]%s(): %s%s\n", (printAnsi_ ? "\033[33m" : ""), name_.c_str(), fileName, lineNumber, funcName, message.c_str(), (printAnsi_ ? "\033[0m" : ""));
    }

    void logInfo(const String &message, const char *funcName, const char *fileName, int lineNumber)
    {
                    Serial.printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
        (printAnsi_ ? "\033[32m" : ""),   // ANSI color for red
        (printName_ ? "[" : ""),      // File location (if enabled)
        (printName_ ? name_.c_str() : ""),       // name (if enabled)
        (printName_ ? "]" : ""),      // File location (if enabled)
        (printLevel_ ? "[E]" : ""),       // Log level (if enabled)
        (printLocation_ ? "[" : ""),      // File location (if enabled)
        (printLocation_ ? fileName : ""), // File name (if enabled)
        (printLocation_ ? ":" : ""),      // File location (if enabled)
        (printLocation_ ? String(lineNumber).c_str() : ""), // Line number (if enabled)
        (printLocation_ ? "] " : ""),      // File location (if enabled)
        (printLocation_ ? funcName : ""),      // Function name (if enabled)
        (printLocation_ ? "(): " : ""),      // File location (if enabled)
        message.c_str(),                  // Log message
        (printAnsi_ ? "\033[0m" : "")     // Reset ANSI color
    );
        // Serial.printf("%s[%s][I][%s:%d]%s(): %s%s\n", (printAnsi_ ? "\033[32m" : ""), name_.c_str(), fileName, lineNumber, funcName, message.c_str(), (printAnsi_ ? "\033[0m" : ""));
    }

    void logDebug(const String &message, const char *funcName, const char *fileName, int lineNumber)
    {
                    Serial.printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
        (printAnsi_ ? "\033[36m" : ""),   // ANSI color for red
        (printName_ ? "[" : ""),      // File location (if enabled)
        (printName_ ? name_.c_str() : ""),       // name (if enabled)
        (printName_ ? "]" : ""),      // File location (if enabled)
        (printLevel_ ? "[E]" : ""),       // Log level (if enabled)
        (printLocation_ ? "[" : ""),      // File location (if enabled)
        (printLocation_ ? fileName : ""), // File name (if enabled)
        (printLocation_ ? ":" : ""),      // File location (if enabled)
        (printLocation_ ? String(lineNumber).c_str() : ""), // Line number (if enabled)
        (printLocation_ ? "] " : ""),      // File location (if enabled)
        (printLocation_ ? funcName : ""),      // Function name (if enabled)
        (printLocation_ ? "(): " : ""),      // File location (if enabled)
        message.c_str(),                  // Log message
        (printAnsi_ ? "\033[0m" : "")     // Reset ANSI color
    );
        // Serial.printf("%s[%s][D][%s:%d]%s(): %s%s\n", (printAnsi_ ? "\033[36m" : ""), name_.c_str(), fileName, lineNumber, funcName, message.c_str(), (printAnsi_ ? "\033[0m" : ""));
    }

    void logVerbose(const String &message, const char *funcName, const char *fileName, int lineNumber)
    {
                    Serial.printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
        (printAnsi_ ? "\033[35m" : ""),   // ANSI color for red
        (printName_ ? "[" : ""),      // File location (if enabled)
        (printName_ ? name_.c_str() : ""),       // name (if enabled)
        (printName_ ? "]" : ""),      // File location (if enabled)
        (printLevel_ ? "[E]" : ""),       // Log level (if enabled)
        (printLocation_ ? "[" : ""),      // File location (if enabled)
        (printLocation_ ? fileName : ""), // File name (if enabled)
        (printLocation_ ? ":" : ""),      // File location (if enabled)
        (printLocation_ ? String(lineNumber).c_str() : ""), // Line number (if enabled)
        (printLocation_ ? "] " : ""),      // File location (if enabled)
        (printLocation_ ? funcName : ""),      // Function name (if enabled)
        (printLocation_ ? "(): " : ""),      // File location (if enabled)
        message.c_str(),                  // Log message
        (printAnsi_ ? "\033[0m" : "")     // Reset ANSI color
    );
        // Serial.printf("%s[%s][V][%s:%d]%s(): %s%s\n", (printAnsi_ ? "\033[35m" : ""), name_.c_str(), fileName, lineNumber, funcName, message.c_str(), (printAnsi_ ? "\033[0m" : ""));
    }
};

#define log_error(debugObj, fmt, ...)                                                          \
    do                                                                                         \
    {                                                                                          \
        String outputString = debugObj.formatString(fmt, ##__VA_ARGS__);                       \
        debugObj.error(__FUNCTION__, __FILE__, __LINE__, outputString.c_str(), ##__VA_ARGS__); \
    } while (0)

#define log_warning(debugObj, fmt, ...)                                                        \
    do                                                                                         \
    {                                                                                          \
        String outputString = debugObj.formatString(fmt, ##__VA_ARGS__);                       \
        debugObj.warning(__FUNCTION__, __FILE__, __LINE__, outputString.c_str(), ##__VA_ARGS__); \
    } while (0)

#define log_info(debugObj, fmt, ...)                                                            \
    do                                                                                         \
    {                                                                                          \
        String outputString = debugObj.formatString(fmt, ##__VA_ARGS__);                       \
        debugObj.info(__FUNCTION__, __FILE__, __LINE__, outputString.c_str(), ##__VA_ARGS__);   \
    } while (0)

#define log_debug(debugObj, fmt, ...)                                                           \
    do                                                                                         \
    {                                                                                          \
        String outputString = debugObj.formatString(fmt, ##__VA_ARGS__);                       \
        debugObj.debug(__FUNCTION__, __FILE__, __LINE__, outputString.c_str(), ##__VA_ARGS__);  \
    } while (0)

#define log_verbose(debugObj, fmt, ...)                                                        \
    do                                                                                         \
    {                                                                                          \
        String outputString = debugObj.formatString(fmt, ##__VA_ARGS__);                       \
        debugObj.verbose(__FUNCTION__, __FILE__, __LINE__, outputString.c_str(), ##__VA_ARGS__); \
    } while (0)