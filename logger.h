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

#ifndef REPORTING_LEVEL
#define REPORTING_LEVEL INFO
#endif

// Loggin macros to be used for logging
#define LOG(LEVEL) \
  if (LEVEL <= REPORTING_LEVEL) \
    Log().get(LEVEL) << TLoggerLevelString[LEVEL] << " " << __TIME__ \
                     << " [" << __FILENAME__ << ":" << __LINE__ << "] "

#define LOG_IF(LEVEL, COND) if (COND) LOG(LEVEL)

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
    ~Log() {
      if (messageLevel <= REPORTING_LEVEL) {
        os << std::endl;
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
