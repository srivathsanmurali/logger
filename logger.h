#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <sstream>
#include <cstdio>
#include <cstring>
#include <stdexcept>

// strips filepath to get filename
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

enum TLoggerLevel {ERROR, WARNING, INFO, DEBUG, DEBUG1, DEBUG2, DEBUG3};
static const char* TLoggerLevelString[] =
                          {"ERROR", "WARNING", "INFO", "DEBUG",
                          "DEBUG1", "DEBUG2", "DEBUG3"};
enum TColorCodes {
  RESET, WHITE, RED, GREEN, YELLOW, BLUE, MAGENTA,
  CYAN, GRAY, BOLD_RED, BOLD_GREEN, BOLD_YELLOW };

static const char* TColorCodesString[] = {
  "\033[0m",      // RESET
  "\033[1m",      // WHITE
  "\033[0;31m",   // RED
  "\033[0;32m",   // GREEN
  "\033[0;33m",   // YELLOW
  "\033[0;34m",   // BLUE
  "\033[0;35m",   // MAGENTA
  "\033[0;36m",   // CYAN
  "\033[1;30m",   // GRAY
  "\033[1;31m",   // BOLD_RED
  "\033[1;32m",   // BOLD_GREEN
  "\033[1;33m"    // BOLD_YELLOW
};


#ifndef REPORTING_LEVEL
#define REPORTING_LEVEL INFO
#endif

// Loggin macros to be used for logging
#define LOG(LEVEL) \
  if (LEVEL <= REPORTING_LEVEL) \
    Log().get(LEVEL) << TLoggerLevelString[LEVEL] << " " << __TIME__ \
                     << " [" << __FILENAME__ << ":" << __LINE__ << "] "

#define LOG_COLOR(LEVEL, COLOR) \
  if (LEVEL <= REPORTING_LEVEL) \
    Log().getColor(LEVEL, COLOR) << TLoggerLevelString[LEVEL] << " " << __TIME__ \
                     << " [" << __FILENAME__ << ":" << __LINE__ << "] "

#define LOG_IF(LEVEL, COND) if (COND) LOG(LEVEL)
#define LOG_IF_COLOR(LEVEL, COND, COLOR) if (COND) LOG_COLOR(LEVEL, COLOR)

// Logging engine class uses loggin level to log to stderr
class Log {
  private:
    TLoggerLevel messageLevel;
    std::ostringstream os;

  public:
    Log():messageLevel(INFO) {}

    std::ostringstream& get(TLoggerLevel level = INFO) {
      messageLevel = level;
      return os;
    }
    std::ostringstream& getColor(
        TLoggerLevel level = INFO,
        TColorCodes color = RESET) {
      messageLevel = level;
      os << TColorCodesString[color];
      return os;
    }
    ~Log() {
      if (messageLevel <= REPORTING_LEVEL) {
        os << std::endl << TColorCodesString[RESET];
        fprintf(stderr, "%s", os.str().c_str());
        fflush(stderr);
      }
    }
};

// throws runtime error with context details.
#define throwRuntimeError(x) \
  std::stringstream ss; \
  ss << "[" << __TIME__ << ":" << __FILENAME__ << ":" << __LINE__ << "] " \
      << x; \
  throw std::runtime_error(ss.str());
#endif // _LOGGER_H_
