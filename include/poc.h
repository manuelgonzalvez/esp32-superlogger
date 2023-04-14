#include "Arduino.h"

class superLoggerPOC
{
public:
    enum LogLevel
    {
        NONE,
        ERROR
    };

    superLoggerPOC(const String &name, LogLevel level = NONE, HardwareSerial &serial = Serial, bool pName = true, bool pLvl = true, bool pAnsi = true, bool pLoc = true) : name_(name), level_(level),serial_(serial), printName_(pName), printLevel_(pLvl), printAnsi_(pAnsi), printLocation_(pLoc) {}



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
    String formatString(const char *format, Args... args)
    {
        char buffer[512];
        snprintf(buffer, sizeof(buffer), format, args...);
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

    void logError(const String &message, const char *funcName, const char *fileName, int lineNumber)
    {
        serial_.printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
                       (printAnsi_ ? "\033[91m" : ""),                     // ANSI color for red
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

};
#define log_error(debugObj, fmt, ...)                                                          \
    do                                                                                         \
    {                                                                                          \
        String outputString = debugObj.formatString(fmt, ##__VA_ARGS__);                       \
        debugObj.error(__FUNCTION__, __FILE__, __LINE__, outputString.c_str(), ##__VA_ARGS__); \
    } while (0)
