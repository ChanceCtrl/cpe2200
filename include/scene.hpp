#pragma once

#include <stdint.h>

#include <Arduino.h>

class scene {
private:
  void (*on_enter_call)() = NULL;

  String intro_text = "";

  String option_1_text = "";
  String option_2_text = "";
  String option_3_text = "";
  String option_4_text = "";

  uint16_t option_1_val = 0;
  uint16_t option_2_val = 0;
  uint16_t option_3_val = 0;
  uint16_t option_4_val = 0;

  bool time_option = false;
  bool time_warning = false;
  String option_time_text = "";
  uint16_t option_time_val = 0;

public:
  void (*warning_call)() = NULL;

  scene(String intro_text, String option_1_text, uint16_t option_1_val,
        String option_2_text, uint16_t option_2_val, String option_3_text,
        uint16_t option_3_val, String option_4_text, uint16_t option_4_val,
        void (*enter_func)()) {
    this->option_1_text = option_1_text;
    this->option_2_text = option_2_text;
    this->option_3_text = option_3_text;
    this->option_4_text = option_4_text;

    this->option_1_val = option_1_val;
    this->option_2_val = option_2_val;
    this->option_3_val = option_3_val;
    this->option_4_val = option_4_val;

    this->on_enter_call = enter_func;

    this->time_option = false;
  }

  scene(String intro_text, String option_1_text, uint16_t option_1_val,
        String option_2_text, uint16_t option_2_val, String option_3_text,
        uint16_t option_3_val, String option_4_text, uint16_t option_4_val) {
    this->option_1_text = option_1_text;
    this->option_2_text = option_2_text;
    this->option_3_text = option_3_text;
    this->option_4_text = option_4_text;

    this->option_1_val = option_1_val;
    this->option_2_val = option_2_val;
    this->option_3_val = option_3_val;
    this->option_4_val = option_4_val;

    this->on_enter_call = NULL;

    this->time_option = false;
  }

  scene(String intro_text, String option_time_text, uint16_t option_time_val,
        String option_1_text, uint16_t option_1_val, String option_2_text,
        uint16_t option_2_val, String option_3_text, uint16_t option_3_val,
        String option_4_text, uint16_t option_4_val, void (*enter_func)()) {
    this->option_1_text = option_1_text;
    this->option_2_text = option_2_text;
    this->option_3_text = option_3_text;
    this->option_4_text = option_4_text;

    this->option_1_val = option_1_val;
    this->option_2_val = option_2_val;
    this->option_3_val = option_3_val;
    this->option_4_val = option_4_val;

    this->on_enter_call = enter_func;

    this->option_time_text = option_time_text;
    this->option_time_val = option_time_val;
    this->time_option = true;

    this->time_warning = false;
  }

  scene(String intro_text, String option_time_text, uint16_t option_time_val,
        String option_1_text, uint16_t option_1_val, String option_2_text,
        uint16_t option_2_val, String option_3_text, uint16_t option_3_val,
        String option_4_text, uint16_t option_4_val) {
    this->option_1_text = option_1_text;
    this->option_2_text = option_2_text;
    this->option_3_text = option_3_text;
    this->option_4_text = option_4_text;

    this->option_1_val = option_1_val;
    this->option_2_val = option_2_val;
    this->option_3_val = option_3_val;
    this->option_4_val = option_4_val;

    this->on_enter_call = NULL;

    this->option_time_text = option_time_text;
    this->option_time_val = option_time_val;
    this->time_option = true;

    this->time_warning = false;
  }

  scene(String intro_text, String option_time_text, uint16_t option_time_val,
        void (*warning_call)(), String option_1_text, uint16_t option_1_val,
        String option_2_text, uint16_t option_2_val, String option_3_text,
        uint16_t option_3_val, String option_4_text, uint16_t option_4_val) {
    this->option_1_text = option_1_text;
    this->option_2_text = option_2_text;
    this->option_3_text = option_3_text;
    this->option_4_text = option_4_text;

    this->option_1_val = option_1_val;
    this->option_2_val = option_2_val;
    this->option_3_val = option_3_val;
    this->option_4_val = option_4_val;

    this->on_enter_call = NULL;

    this->option_time_text = option_time_text;
    this->option_time_val = option_time_val;
    this->time_option = true;

    this->time_warning = true;
    this->warning_call = warning_call;
  }

  scene(String intro_text, String option_time_text, uint16_t option_time_val,
        void (*warning_call)(), String option_1_text, uint16_t option_1_val,
        String option_2_text, uint16_t option_2_val, String option_3_text,
        uint16_t option_3_val, String option_4_text, uint16_t option_4_val,
        void (*enter_func)()) {
    this->option_1_text = option_1_text;
    this->option_2_text = option_2_text;
    this->option_3_text = option_3_text;
    this->option_4_text = option_4_text;

    this->option_1_val = option_1_val;
    this->option_2_val = option_2_val;
    this->option_3_val = option_3_val;
    this->option_4_val = option_4_val;

    this->on_enter_call = enter_func;

    this->option_time_text = option_time_text;
    this->option_time_val = option_time_val;
    this->time_option = true;

    this->time_warning = true;
    this->warning_call = warning_call;
  }

  void print_options() {
    if (on_enter_call != NULL) {
      on_enter_call();
    }

    Serial.println(intro_text);

    // Don't print unused options
    if (option_1_text != "") {
      Serial.print("\n1: ");
      Serial.println(option_1_text);
    }

    if (option_2_text != "") {
      Serial.print("2: ");
      Serial.println(option_2_text);
    }

    if (option_3_text != "") {
      Serial.print("3: ");
      Serial.println(option_3_text);
    }

    if (option_4_text != "") {
      Serial.print("4: ");
      Serial.println(option_4_text);
    }

    Serial.print("What will you do?\n");
  }

  void time_print() {
    if (option_time_text != "") {
      Serial.println(option_time_text);
    }
  }

  // Will default to option_1_val if the option has no text but somehow gets
  // selected
  uint16_t get_return(uint8_t direction) {
    switch (direction) {
    case 0:
      if (option_time_text != "") {
        return option_time_val;
      } else {
        return option_1_val;
      }
    case 1:
      if (option_1_text != "") {
        return option_1_val;
      } else {
        return option_1_val;
      }
    case 2:
      if (option_2_text != "") {
        return option_2_val;
      } else {
        return option_1_val;
      }
    case 3:
      if (option_3_text != "") {
        return option_3_val;
      } else {
        return option_1_val;
      }
    case 4:
      if (option_4_text != "") {
        return option_4_val;
      } else {
        return option_1_val;
      }

    default:
      return 0;
    }
  };

  inline bool has_time_option() { return this->time_option; }

  inline bool has_time_warning() { return this->time_warning; }
};
