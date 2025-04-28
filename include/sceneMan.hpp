#pragma once

// For the Serial & delay commands
#include <Arduino.h>

#include "art.hpp"
#include "scene.hpp"
#include "timeMan.hpp"

bool is_won = false;

char fella[100];

String get_name() { return String(fella); };

int HARD_TTK = 6;
int EASY_TTK = 12;
const int SCENE_COUNT = 50;

bool has_MLS = false;
bool has_good_object = false;
bool has_evil_object = false;

uint16_t test_count = 0;

bool has_warned = false;
bool has_warned2 = false;

void time_warn() {
  if (!has_warned) {
    Serial.println("They hear some people enter and start talking");
    has_warned = true;
  }
}

void time_warn_2() {
  if (!has_warned2) {
    Serial.println(get_name() + " Sees some scribbles on the wall that look "
                                "like some arrows... <- -> <- ^");
  }
}

// Re using this for death
void player_is_kill() { is_won = true; }

void player_has_won() {
  is_won = true;
  print_outside();
}

timeMan hard_timer(HARD_TTK, false);
timeMan easy_timer(EASY_TTK, false);

class sceneMan {
private:
  uint16_t scene_index = 1;

  scene stage[SCENE_COUNT] = {
      // 0
      scene("How did you get here?", "", 0, "", 0, "", 0, "", 0),

      // 1
      scene("\n", "Log in " + get_name() + "?", 2, "", 0, "", 0, "", 0,
            &print_title),

      // 2
      scene("The terminal flickers a few times, and then goes blank...",
            get_name() + " sees some group of people come into the room", 4,
            "Try to log off...", 3, "Leave " + get_name() + "'s desk", 5, "", 3,
            "", 3),
      // 3
      scene(get_name() +
                " attempts to shut off the computer and leave the building, "
                "but they are stopped at the door and told to get back to work",
            "Go back", 2, "", 0, "", 0, "", 0),

      // 4
      scene("Soon armed people surrond" + get_name() +
                ", and their cubical is gone the next day...",
            "", 4, "", 4, "", 4, "", 4, "", 4, &player_is_kill),

      // 5
      scene(get_name() +
                " starts to wander, soon finding themselves in a hallway",
            "They hear some group of people getting closer and start to walk "
            "faster...",
            6, "Go to restroom", 13, "Continue down the halls", 6, "", 3, "",
            4),

      // 6
      scene(get_name() + " notices that the halls are slowly turning from "
                         "simple black trim and cream carpet style to a smooth "
                         "silver corridor as they go down a series of stairs",
            "Look at the patterns", 7, "Run faster", 9, "", 0, "", 0),

      // 7
      scene(
          get_name() +
              " looks at the walls a little closer, finding the name of the "
              "company embossed on the surface, hundreds of times per square "
              "foot, but still readable... As they run their fingers across it "
              "they feel a static charge and are soon eletrecuted to death...",
          "", 0, "", 0, "", 0, "", 0, &player_is_kill),

      // 8  NOTE: UNUSED
      scene(get_name() + " hears what they assume now to be the companies PMC "
                         "and start running",
            "", 0, "", 0, "", 0, "", 0),

      // 9
      scene(get_name() + " starts to feel their hair rise...",
            "soon a charge forms on the walls and zaps " + get_name(), 49,
            "Stand in place", 10, "Dive to the ground", 11, "", 0, "", 0),

      // 10
      scene("What " + get_name() +
                " assumes now to be the PMC of the company round the corner, "
                "and start to raise something " +
                get_name() + " dives for cover and the soldiers are zapped",
            "Brace", 11, "", 0, "", 0, "", 0),

      // 11
      scene("The ground beneath them rips away like aluminium foil, they fall "
            "through multiple more floors all ripping away",
            "...", 12, "", 0, "", 0, "", 0),

      // 12
      scene(get_name() + " wakes up in a long thin hallway", "", 0, "", 0, "",
            0, "", 0),

      // 13
      scene(get_name() + " quickly steps into the restroom",
            "The people who entered start talking about how some of the "
            "newbies have been getting marked for 'expirey' and that in the "
            "past it just meant getting thrown onto the street, they start to "
            "open the door that " +
                get_name() + " and panick",
            16, &time_warn, "Look around", 15, "", 0, "", 0, "", 0),

      // 14  NOTE: UNUSED
      scene("", "", 0, "", 0, "", 0, "", 0),

      // 15
      scene("They see a vent and start to kick it open, after it pops off with "
            "a loud bang " +
                get_name() + " quickly jumps in...",
            get_name() + " is then smitted by an eletric charge", 49,
            &time_warn_2, "Start crawling", 19, "", 0, "", 0, "", 0),

      // 16
      scene(get_name() +
                " is then slapped, punched and thrown around for a bit",
            "wake up", 17, "", 0, "", 0, "", 0),

      // 17
      scene(get_name() + " is casted onto the street, and limps away...", "", 0,
            "", 0, "", 0, "", 0, &player_has_won),

      // 18
      scene("Another split...", "They sit still...", 48, "Go left", 48,
            "Go straight", 48, "Go right", 48, "", 0),

      // 19
      scene(get_name() + " starts to akwarding shuffle and soon finds a split",
            "Go left", 20, "Go right", 18, "", 0, "", 0),

      // 20
      scene(get_name() + "hears people bellow...", "They sit still...", 48, "",
            0, "", 0, "", 0, "", 0),

      // 21
      scene("", "", 0, "", 0, "", 0, "", 0),

      // 22
      scene("", "", 0, "", 0, "", 0, "", 0),

      // 23
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 24
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 25
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 26
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 27
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 28
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 29
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 30
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 31
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 32
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 33
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 34
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 35
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 36
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 37
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 38
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 39
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 40
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 41
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 42
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 43
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 44
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 45
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 46
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 47
      scene("", "", 0, "", 0, "", 0, "", 0),
      // 48
      scene(get_name() +
                " starts to feel the electricty build, they are then zapped",
            "", 0, "", 0, "", 0, "", 0, &player_is_kill),
      // 49
      scene(get_name() + " is dead.", "", 0, "", 0, "", 0, "", 0,
            &player_is_kill),
  };

public:
  timeMan *timer;

  void set_difficulty(int target_difficulty) {
    switch (target_difficulty) {
    case 0:
      timer = &hard_timer;
      timer->reset_check();
      break;
    case 1:
      timer = &easy_timer;
      timer->reset_check();
      break;
    }
  }

  void update(int input) {
    // Make sure the input makes sense
    if (input >= 1 && input <= 4) {
      scene_index = stage[scene_index].get_return(input);
      stage[scene_index].print_options();

      timer->reset_check();
    }

    // Print user help if they mess it up
    else {
      Serial.printf(
          "%i is not a valid choice, please choose something real...\n", input);
    }
  }

  void update(long current_time) {
    timer->update(current_time);

    if (timer->get_delta() > 3 && stage[scene_index].has_time_warning()) {
      stage[scene_index].warning_call();
    }

    if (timer->check() && stage[scene_index].has_time_option()) {
      stage[scene_index].time_print();

      if (stage[scene_index].get_return(0) != 0) {
        scene_index = stage[scene_index].get_return(0);

        stage[scene_index].print_options();

        timer->reset_check();
      }
    }
  }

  void set_scene(uint16_t target_scene) {
    scene_index = target_scene;
    this->stage[scene_index].print_options();

    timer->reset_check();
  }
};
