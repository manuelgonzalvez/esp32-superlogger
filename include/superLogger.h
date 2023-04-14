#include "Arduino.h"

#define MAX_BUFFER_SIZE 50
#define THROW_EXCEPTION_ON_OVERFLOW true

#define ANSI_RED        "\033[91m"
#define ANSI_PURPLE     "\033[35m"
#define ANSI_YELLOW     "\033[33m"
#define ANSI_GREEN      "\033[32m"
#define ANSI_BLUE       "\033[36m"
class superLogger
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

    superLogger(const String &name, LogLevel level = NONE, HardwareSerial &serial = Serial, bool pName = true, bool pLvl = true, bool pAnsi = true, bool pLoc = true) : name_(name), level_(level), serial_(serial), printName_(pName), printLevel_(pLvl), printAnsi_(pAnsi), printLocation_(pLoc) {}

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
            log(outputString, funcName, fileName, lineNumber, ANSI_RED);
        }
    }

    // template <typename... Args>
    // void error(const char *funcName, const char *fileName, int lineNumber, const String &format, Args... args)
    // {
    //     if (level_ >= ERROR)
    //     {
    //         String outputString = formatString(format.c_str(), args...);
    //         log(outputString, funcName, fileName, lineNumber,ANSI_RED);
    //     }
    // }

    template <typename... Args>
    void warning(const char *funcName, const char *fileName, int lineNumber, const char *format, Args... args)
    {
        if (level_ >= WARNING)
        {
            String outputString = formatString(format, args...);
            log(outputString, funcName, fileName, lineNumber, ANSI_YELLOW);
        }
    }

    template <typename... Args>
    void info(const char *funcName, const char *fileName, int lineNumber, const char *format, Args... args)
    {
        if (level_ >= INFO)
        {
            String outputString = formatString(format, args...);
            log(outputString, funcName, fileName, lineNumber,ANSI_GREEN);
        }
    }

    template <typename... Args>
    void debug(const char *funcName, const char *fileName, int lineNumber, const char *format, Args... args)
    {
        if (level_ >= DEBUG)
        {
            String outputString = formatString(format, args...);
            log(outputString, funcName, fileName, lineNumber,ANSI_BLUE);
        }
    }

    template <typename... Args>
    void verbose(const char *funcName, const char *fileName, int lineNumber, const char *format, Args... args)
    {
        if (level_ >= VERBOSE)
        {
            String outputString = formatString(format, args...);
            log(outputString, funcName, fileName, lineNumber, ANSI_PURPLE);
        }
    }






    // template <typename... Args>
    // String formatString(const char *format, Args... args)
    // {
    //     char buffer[MAX_BUFFER_SIZE];
    //     snprintf(buffer, sizeof(buffer), format, args...);
    //     return String(buffer);
    // }

    template <typename... Args>
    String formatString(const String &message)
    {
        return message;
    }





template <typename... Args>
String formatString(const char *format, Args... args)
{
    char buffer[MAX_BUFFER_SIZE];
    int result = snprintf(buffer, sizeof(buffer), format, args...);
    if (result < 0) {
        // throw std::runtime_error("Error in formatString(): snprintf returned a negative value.");
    }
    int messageSize = result + 1; // add 1 to account for null terminator
    if (messageSize > MAX_BUFFER_SIZE) {
#if THROW_EXCEPTION_ON_OVERFLOW
        // throw log_e("Error in formatString(): Message size exceeds maximum buffer size.");
        return "ERR_EXCEEDS_BUFFER";
#else
        String message;
        message.reserve(messageSize);
        result = snprintf(&message[0], messageSize, format, args...);
        if (result < 0) {
            throw std::runtime_error("Error in formatString(): snprintf returned a negative value.");
        }
        return message;
#endif
    }
    return String(buffer);
}


private:
    String name_;
    LogLevel level_;
    HardwareSerial &serial_;
    bool printName_;
    bool printLevel_;
    bool printAnsi_;
    bool printLocation_;

    void log(const String &message, const char *funcName, const char *fileName, int lineNumber, const char *color)
    {
        serial_.printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
                       (printAnsi_ ? color : ""),                          // ANSI color
                       (printName_ ? "[" : ""),                            // File location (if enabled)
                       (printName_ ? name_.c_str() : ""),                  // name (if enabled)
                       (printName_ ? "]" : ""),                            // File location (if enabled)
                       (printLevel_ ? "[E]" : ""),                         // Log level (if enabled)
                       (printLocation_ ? "[" : ""),                        // File location (if enabled)
                       (printLocation_ ? fileName : ""),                   // File name (if enabled)
                       (printLocation_ ? ":" : ""),                        // File location (if enabled)
                       (printLocation_ ? String(lineNumber).c_str() : ""), // Line number (if enabled)
                       (printLocation_ ? "] " : ""),                       // File location (if enabled)
                       (printLocation_ ? funcName : ""),                   // Function name (if enabled)
                       (printLocation_ ? "(): " : ""),                     // File location (if enabled)
                       message.c_str(),                                    // Log message
                       (printAnsi_ ? "\033[0m" : "")                       // Reset ANSI color
        );
    }
    // void logError(const String &message, const char *funcName, const char *fileName, int lineNumber)
    // {
    //     serial_.printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
    //                    (printAnsi_ ? "\033[91m" : ""),                     // ANSI color for red
    //                    (printName_ ? "[" : ""),                            // File location (if enabled)
    //                    (printName_ ? name_.c_str() : ""),                  // name (if enabled)
    //                    (printName_ ? "]" : ""),                            // File location (if enabled)
    //                    (printLevel_ ? "[E]" : ""),                         // Log level (if enabled)
    //                    (printLocation_ ? "[" : ""),                        // File location (if enabled)
    //                    (printLocation_ ? fileName : ""),                   // File name (if enabled)
    //                    (printLocation_ ? ":" : ""),                        // File location (if enabled)
    //                    (printLocation_ ? String(lineNumber).c_str() : ""), // Line number (if enabled)
    //                    (printLocation_ ? "] " : ""),                       // File location (if enabled)
    //                    (printLocation_ ? funcName : ""),                   // Function name (if enabled)
    //                    (printLocation_ ? "(): " : ""),                     // File location (if enabled)
    //                    message.c_str(),                                    // Log message
    //                    (printAnsi_ ? "\033[0m" : "")                       // Reset ANSI color
    //     );
    // }

    // void logWarning(const String &message, const char *funcName, const char *fileName, int lineNumber)
    // {
    //     serial_.printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
    //                    (printAnsi_ ? "\033[33m" : ""),                     // ANSI color for red
    //                    (printName_ ? "[" : ""),                            // File location (if enabled)
    //                    (printName_ ? name_.c_str() : ""),                  // name (if enabled)
    //                    (printName_ ? "]" : ""),                            // File location (if enabled)
    //                    (printLevel_ ? "[E]" : ""),                         // Log level (if enabled)
    //                    (printLocation_ ? "[" : ""),                        // File location (if enabled)
    //                    (printLocation_ ? fileName : ""),                   // File name (if enabled)
    //                    (printLocation_ ? ":" : ""),                        // File location (if enabled)
    //                    (printLocation_ ? String(lineNumber).c_str() : ""), // Line number (if enabled)
    //                    (printLocation_ ? "] " : ""),                       // File location (if enabled)
    //                    (printLocation_ ? funcName : ""),                   // Function name (if enabled)
    //                    (printLocation_ ? "(): " : ""),                     // File location (if enabled)
    //                    message.c_str(),                                    // Log message
    //                    (printAnsi_ ? "\033[0m" : "")                       // Reset ANSI color
    //     );
    //     // Serial.printf("%s[%s][W][%s:%d]%s(): %s%s\n", (printAnsi_ ? "\033[33m" : ""), name_.c_str(), fileName, lineNumber, funcName, message.c_str(), (printAnsi_ ? "\033[0m" : ""));
    // }

    // void logInfo(const String &message, const char *funcName, const char *fileName, int lineNumber)
    // {
    //     serial_.printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
    //                    (printAnsi_ ? "\033[32m" : ""),                     // ANSI color for red
    //                    (printName_ ? "[" : ""),                            // File location (if enabled)
    //                    (printName_ ? name_.c_str() : ""),                  // name (if enabled)
    //                    (printName_ ? "]" : ""),                            // File location (if enabled)
    //                    (printLevel_ ? "[E]" : ""),                         // Log level (if enabled)
    //                    (printLocation_ ? "[" : ""),                        // File location (if enabled)
    //                    (printLocation_ ? fileName : ""),                   // File name (if enabled)
    //                    (printLocation_ ? ":" : ""),                        // File location (if enabled)
    //                    (printLocation_ ? String(lineNumber).c_str() : ""), // Line number (if enabled)
    //                    (printLocation_ ? "] " : ""),                       // File location (if enabled)
    //                    (printLocation_ ? funcName : ""),                   // Function name (if enabled)
    //                    (printLocation_ ? "(): " : ""),                     // File location (if enabled)
    //                    message.c_str(),                                    // Log message
    //                    (printAnsi_ ? "\033[0m" : "")                       // Reset ANSI color
    //     );
    //     // Serial.printf("%s[%s][I][%s:%d]%s(): %s%s\n", (printAnsi_ ? "\033[32m" : ""), name_.c_str(), fileName, lineNumber, funcName, message.c_str(), (printAnsi_ ? "\033[0m" : ""));
    // }

    // void logDebug(const String &message, const char *funcName, const char *fileName, int lineNumber)
    // {
    //     serial_.printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
    //                    (printAnsi_ ? "\033[36m" : ""),                     // ANSI color for red
    //                    (printName_ ? "[" : ""),                            // File location (if enabled)
    //                    (printName_ ? name_.c_str() : ""),                  // name (if enabled)
    //                    (printName_ ? "]" : ""),                            // File location (if enabled)
    //                    (printLevel_ ? "[E]" : ""),                         // Log level (if enabled)
    //                    (printLocation_ ? "[" : ""),                        // File location (if enabled)
    //                    (printLocation_ ? fileName : ""),                   // File name (if enabled)
    //                    (printLocation_ ? ":" : ""),                        // File location (if enabled)
    //                    (printLocation_ ? String(lineNumber).c_str() : ""), // Line number (if enabled)
    //                    (printLocation_ ? "] " : ""),                       // File location (if enabled)
    //                    (printLocation_ ? funcName : ""),                   // Function name (if enabled)
    //                    (printLocation_ ? "(): " : ""),                     // File location (if enabled)
    //                    message.c_str(),                                    // Log message
    //                    (printAnsi_ ? "\033[0m" : "")                       // Reset ANSI color
    //     );
    //     // Serial.printf("%s[%s][D][%s:%d]%s(): %s%s\n", (printAnsi_ ? "\033[36m" : ""), name_.c_str(), fileName, lineNumber, funcName, message.c_str(), (printAnsi_ ? "\033[0m" : ""));
    // }

    // void logVerbose(const String &message, const char *funcName, const char *fileName, int lineNumber)
    // {
    //     serial_.printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
    //                    (printAnsi_ ? "\033[35m" : ""),                     // ANSI color for red
    //                    (printName_ ? "[" : ""),                            // File location (if enabled)
    //                    (printName_ ? name_.c_str() : ""),                  // name (if enabled)
    //                    (printName_ ? "]" : ""),                            // File location (if enabled)
    //                    (printLevel_ ? "[E]" : ""),                         // Log level (if enabled)
    //                    (printLocation_ ? "[" : ""),                        // File location (if enabled)
    //                    (printLocation_ ? fileName : ""),                   // File name (if enabled)
    //                    (printLocation_ ? ":" : ""),                        // File location (if enabled)
    //                    (printLocation_ ? String(lineNumber).c_str() : ""), // Line number (if enabled)
    //                    (printLocation_ ? "] " : ""),                       // File location (if enabled)
    //                    (printLocation_ ? funcName : ""),                   // Function name (if enabled)
    //                    (printLocation_ ? "(): " : ""),                     // File location (if enabled)
    //                    message.c_str(),                                    // Log message
    //                    (printAnsi_ ? "\033[0m" : "")                       // Reset ANSI color
    //     );
    //     // Serial.printf("%s[%s][V][%s:%d]%s(): %s%s\n", (printAnsi_ ? "\033[35m" : ""), name_.c_str(), fileName, lineNumber, funcName, message.c_str(), (printAnsi_ ? "\033[0m" : ""));
    // }
};

#define log_error(debugObj, fmt, ...)                                                          \
    do                                                                                         \
    {                                                                                          \
        String outputString = debugObj.formatString(fmt, ##__VA_ARGS__);                       \
        debugObj.error(__FUNCTION__, __FILE__, __LINE__, outputString.c_str(), ##__VA_ARGS__); \
    } while (0)

#define log_warning(debugObj, fmt, ...)                                                          \
    do                                                                                           \
    {                                                                                            \
        String outputString = debugObj.formatString(fmt, ##__VA_ARGS__);                         \
        debugObj.warning(__FUNCTION__, __FILE__, __LINE__, outputString.c_str(), ##__VA_ARGS__); \
    } while (0)

#define log_info(debugObj, fmt, ...)                                                          \
    do                                                                                        \
    {                                                                                         \
        String outputString = debugObj.formatString(fmt, ##__VA_ARGS__);                      \
        debugObj.info(__FUNCTION__, __FILE__, __LINE__, outputString.c_str(), ##__VA_ARGS__); \
    } while (0)

#define log_debug(debugObj, fmt, ...)                                                          \
    do                                                                                         \
    {                                                                                          \
        String outputString = debugObj.formatString(fmt, ##__VA_ARGS__);                       \
        debugObj.debug(__FUNCTION__, __FILE__, __LINE__, outputString.c_str(), ##__VA_ARGS__); \
    } while (0)

#define log_verbose(debugObj, fmt, ...)                                                          \
    do                                                                                           \
    {                                                                                            \
        String outputString = debugObj.formatString(fmt, ##__VA_ARGS__);                         \
        debugObj.verbose(__FUNCTION__, __FILE__, __LINE__, outputString.c_str(), ##__VA_ARGS__); \
    } while (0)