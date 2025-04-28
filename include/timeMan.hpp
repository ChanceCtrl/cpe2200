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
    bool result;

    // Test code
    // if ((current_time - check_epoch) > check_time) {
    //   // Auto adjust our epoch so we can continously check for things
    //   if (auto_reset_enabled) {
    //     check_epoch = current_time;
    //   }
    //
    //   result = true;
    // } else
    //   result = false;

    asm volatile(
        // current_time - check_epoch
        "subs %[current_time], %[check_epoch], %[current_time]\n"

        // Compare the result with check_time
        "cmp %[current_time], %[check_time]\n"

        // If (current_time - check_epoch) <= check_time, jump to no_reset
        "ble no_reset\n"

        // Set check_epoch = current_time since condition passed
        "mov %[check_epoch], %[current_time]\n"

        "no_reset:"
        // Set result = true (1) if the check passed
        "mov %[result], #1\n"

        "b done\n" // Jump to done

        "false_result:"
        // Set result = false (0) if the check failed
        "mov %[result], #0\n"

        "done:"
        : [result] "=r"(result),            // Output: result
          [check_epoch] "=r"(check_epoch)   // Output: updated check_epoch
        : [current_time] "r"(current_time), // Input: current_time
          [check_time] "r"(check_time)      // Input: check_time
        : "cc", "r3"                        // Condition flags, temp register
    );

    return result;
  }

  inline long get_time() { return current_time; }

  // More test code
  // inline long get_delta() { return current_time - check_epoch; }

  long get_delta() {
    long delta;
    asm volatile(
        // Calculate the delta (current_time - check_epoch)
        "subs    %[delta], %[current_time], %[check_epoch] \n" // delta =
                                                               // current_time -
                                                               // check_epoch
        : [delta] "=r"(delta)                                  // Output: delta
        : [current_time] "r"(current_time), // Input: current_time
          [check_epoch] "r"(check_epoch)    // Input: check_epoch
        : "cc"                              // Condition flags are modified
    );

    return delta;
  }
};
