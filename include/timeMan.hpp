#pragma once

#include <stdint.h>

class timeMan {
private:
  long start_epoch = 0;
  long current_time = 0;

  // Check function related defs
  uint32_t check_epoch = 0;
  uint32_t check_time = 0;
  bool auto_reset_enabled = false;

public:
  timeMan(uint32_t check_time, bool auto_reset_enabled) {
    this->check_time = check_time;
    this->auto_reset_enabled = auto_reset_enabled;
  }

  inline void update(long current_time) { this->current_time = current_time; }

  // Manually adjust our epoch so we can do things before starting to check
  inline void reset_check() { check_epoch = current_time; }

  bool check() {
    if ((current_time - check_epoch) > check_time) {
      // Auto adjust our epoch so we can continously check for things
      if (auto_reset_enabled) {
        check_epoch = current_time;
      }

      return true;
    }

    else
      return false;
  }

  inline long get_time() { return current_time; }

  inline long get_delta() { return current_time - check_epoch; }
};
