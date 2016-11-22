#define REPORTING_LEVEL DEBUG
#include "logger.h"

int main() {
  const size_t cnt = 10;
  LOG(INFO) << "Counter ahead";
  for (size_t i = 0; i < cnt; i++) {
    LOG_IF(DEBUG, i%2==0) << i;
  }
}
