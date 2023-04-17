#include "Arduino.h"

#define MAX_BUFFER_SIZE 512
#define THROW_EXCEPTION_ON_OVERFLOW true

#define ANSI_RED "\033[91m"
#define ANSI_PURPLE "\033[35m"
#define ANSI_YELLOW "\033[33m"
#define ANSI_GREEN "\033[32m"
#define ANSI_BLUE "\033[36m"

#define ANSI_BG_RED "\033[41;37m"
#define ANSI_BG_PURPLE "\033[45;37m"
#define ANSI_BG_YELLOW "\033[43;30m"
#define ANSI_BG_GREEN "\033[42;30m"
#define ANSI_BG_BLUE "\033[46;37m"

#define LEVEL_V "[V]"
#define LEVEL_D "[D]"
#define LEVEL_I "[I]"
#define LEVEL_W "[W]"
#define LEVEL_E "[E]"

#define EXCEEDS_MSG "MSG_EXCEEDS_BUFFER"
class superLogger
{
public:
    enum 
    {
        NONE,
        ERROR,
        WARNING,
        INFO,
        DEBUG,
        VERBOSE
    }LogLevel;

    superLogger(const String &name, uint8_t level = NONE, HardwareSerial &serial = Serial, bool pName = true, bool pLvl = true, bool pAnsi = true, bool pLoc = true) : name_(name), level_(level), serial_(serial), printName_(pName), printLevel_(pLvl), printAnsi_(pAnsi), printLocation_(pLoc) {}

    void setName(const String &name)
    {
        name_ = name;
    }

    void setLevel(uint8_t level)
    {
        level_ = level;
    }
    uint8_t getLevel()
    {
        return level_;
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
    void setHighlight(bool set)
    {
        highlight = set;
    }

    template <typename... Args>
    void __attribute__((noinline)) error(const char *funcName, const char *fileName, int lineNumber, const char *format, Args... args)
    {
        if (level_ >= ERROR)
        {
            String outputString = formatString(format, args...);
            log(outputString, funcName, fileName, lineNumber, ((((outputString == EXCEEDS_MSG) || highlight) ? true : false) ? ANSI_BG_RED : ANSI_RED), LEVEL_E);
        }
    }

    template <typename... Args>
    void __attribute__((noinline)) warning(const char *funcName, const char *fileName, int lineNumber, const char *format, Args... args)
    {
        if (level_ >= WARNING)
        {
            String outputString = formatString(format, args...);
            log(outputString, funcName, fileName, lineNumber, ((((outputString == EXCEEDS_MSG) || highlight) ? true : false) ? ANSI_BG_YELLOW : ANSI_YELLOW), LEVEL_W);
        }
    }

    template <typename... Args>
    void __attribute__((noinline)) info(const char *funcName, const char *fileName, int lineNumber, const char *format, Args... args)
    {
        if (level_ >= INFO)
        {
            String outputString = formatString(format, args...);
            log(outputString, funcName, fileName, lineNumber, ((((outputString == EXCEEDS_MSG) || highlight) ? true : false) ? ANSI_BG_GREEN : ANSI_GREEN), LEVEL_I);
        }
    }

    template <typename... Args>
    void __attribute__((noinline)) debug(const char *funcName, const char *fileName, int lineNumber, const char *format, Args... args)
    {
        if (level_ >= DEBUG)
        {
            String outputString = formatString(format, args...);
            log(outputString, funcName, fileName, lineNumber, ((((outputString == EXCEEDS_MSG) || highlight) ? true : false) ? ANSI_BG_BLUE : ANSI_BLUE), LEVEL_D);
        }
    }

    template <typename... Args>
    void __attribute__((noinline)) verbose(const char *funcName, const char *fileName, int lineNumber, const char *format, Args... args)
    {
        if (level_ >= VERBOSE)
        {
            String outputString = formatString(format, args...);
            log(outputString, funcName, fileName, lineNumber, ((((outputString == EXCEEDS_MSG) || highlight) ? true : false) ? ANSI_BG_PURPLE : ANSI_PURPLE), LEVEL_V);
        }
    }

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
        if (result < 0)
        {
        }
        int messageSize = result + 1; // add 1 to account for null terminator
        if (messageSize > MAX_BUFFER_SIZE)
        {
#if THROW_EXCEPTION_ON_OVERFLOW
            return EXCEEDS_MSG;
#else
            String message;
            message.reserve(messageSize);
            result = snprintf(&message[0], messageSize, format, args...);
            if (result < 0)
            {
                throw std::runtime_error("Error in formatString(): snprintf returned a negative value.");
            }
            return message;
#endif
        }
        return String(buffer);
    }

private:
    String name_;
    uint8_t level_;
    HardwareSerial &serial_;
    bool printName_;
    bool printLevel_;
    bool printAnsi_;
    bool printLocation_;
    bool highlight = false;

    void __attribute__((noinline)) log(const String &message, const char *funcName, const char *fileName, int lineNumber, const char *color, char *levelLetter)
    {
        serial_.printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
                       (printAnsi_ ? color : ""),                          // ANSI color
                       (printName_ ? "[" : ""),                            // File location (if enabled)
                       (printName_ ? name_.c_str() : ""),                  // name (if enabled)
                       (printName_ ? "]" : ""),                            // File location (if enabled)
                       (printLevel_ ? levelLetter : ""),                   // Log level (if enabled)
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