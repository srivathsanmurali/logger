# logger
A simple logger for C++ projects

## Logger levels
The logging levels are in this order. When the reporting level for the logger is specified, all logging levels below it are
reported.
+ ERROR
+ WARNING
+ INFO
+ DEBUG
+ DEBUG1
+ DEBUG2
+ DEUBG3

## Usage
```C++
#define REPORTING_LEVEL DEBUG // Maximum logging level is DEBUG
#include "logger.h"

int main() {
  const size_t cnt = 10;
  // LOGS all the messages since INFO is lower than debug
  LOG(INFO) << "Counter ahead";
  for (size_t i = 0; i < cnt; i++) {
    // LOGS only every other iteration when the condition is satisfied
    LOG_IF(DEBUG, i%2==0) << i;
  }
}
```

## Output from example
```shell
INFO 09:56:45 [example.cc:6] Counter ahead
DEBUG 09:56:45 [example.cc:8] 0
DEBUG 09:56:45 [example.cc:8] 2
DEBUG 09:56:45 [example.cc:8] 4
DEBUG 09:56:45 [example.cc:8] 6
DEBUG 09:56:45 [example.cc:8] 8
```

## Author
Srivathsan (sri@vathsan.com)
