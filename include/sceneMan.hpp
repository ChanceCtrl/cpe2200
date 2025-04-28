#pragma once

// For the Serial & delay commands
#include <Arduino.h>

#include "art.hpp"
#include "scene.hpp"
#include "timeMan.hpp"

bool is_won = false;

char fella[100];
String string_fella = String(fella);

const String fella_string = "Chance";

int HARD_TTK = 6;
int EASY_TTK = 12;
const int SCENE_COUNT = 50;

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
    Serial.println(fella_string + " sees some scribbles on the wall that look "
                                  "like some arrows... <- -> <- ↑");
  }
}

// Re using this for death
void player_is_kill() { is_won = true; }

void player_has_won() {
  is_won = true;
  print_outside();
}

bool has_MLS = false;
bool has_object = false;

void get_object() { has_object = true; }
void get_mls() { has_MLS = true; }

timeMan hard_timer(HARD_TTK, false);
timeMan easy_timer(EASY_TTK, false);

class sceneMan {
private:
  uint16_t scene_index = 1;

  void final_check() {
    if (has_object) {
      Serial.println(
          "The trinket seems to light up, and after a breif white flash " +
          fella_string + "passes out");

      set_scene(17);
    } else if (has_MLS) {
      Serial.println("This fuzzy feeling spreads across " + fella_string +
                     "'s body, as time goes on they notice that the feeling is "
                     "going away, and so was pretty much every feeling... they "
                     "drift off to sleep");

      Serial.println("Thats it for 'them'");
      is_won = true;
    } else {
      set_scene(49);
    }
  }

  void mls_check() {
    if (has_MLS) {
      set_scene(36);
    }
  }

  scene stage[SCENE_COUNT] = {
      // 0
      scene("How did you get here?", "", 0, "", 0, "", 0, "", 0),

      // 1
      scene("", "Log in " + fella_string + "?", 2, "", 0, "", 0, "", 0,
            &print_title),

      // 2
      scene("The terminal flickers a few times, and then goes blank...",
            fella_string + " sees some group of people come into the room", 4,
            "Try to log off...", 3, "Leave " + fella_string + "'s desk", 5, "",
            3, "", 3),
      // 3
      scene(fella_string +
                " attempts to shut off the computer and leave the building, "
                "but they are stopped at the door and told to get back to "
                "work",
            "Go back", 2, "", 0, "", 0, "", 0),

      // 4
      scene("Soon armed people surrond " + fella_string +
                ", and their cubical is gone the next day...",
            "", 4, "", 4, "", 4, "", 4, "", 4, &player_is_kill),

      // 5
      scene(fella_string +
                " starts to wander, soon finding themselves in a hallway",
            "They hear some group of people getting closer and start to walk "
            "faster...",
            6, "Go to restroom", 13, "Continue down the halls", 6, "", 3, "",
            4),

      // 6
      scene(fella_string +
                " notices that the halls are slowly turning from "
                "simple black trim and cream carpet style to a smooth "
                "silver corridor as they go down a series of stairs",
            "Look at the patterns", 7, "Run faster", 9, "", 0, "", 0),

      // 7
      scene(fella_string + " looks at the walls a little closer, finding "
                           "the name of the "
                           "company embossed on the surface, hundreds of "
                           "times per square "
                           "foot, but still readable... As they run their "
                           "fingers across it "
                           "they feel a static charge and are soon "
                           "eletrecuted to death...",
            "", 0, "", 0, "", 0, "", 0, &player_is_kill),

      // 8  NOTE: UNUSED
      scene(fella_string +
                " hears what they assume now to be the companies PMC "
                "and start running",
            "", 0, "", 0, "", 0, "", 0),

      // 9
      scene(fella_string + " starts to feel their hair rise...",
            "soon a charge forms on the walls and zaps " + fella_string, 49,
            "Stand in place", 10, "Dive to the ground", 11, "", 0, "", 0),

      // 10
      scene("What " + fella_string +
                " assumes now to be the PMC of the company round the corner, "
                "and start to raise something " +
                fella_string + " dives for cover and the soldiers are zapped",
            "Brace", 11, "", 0, "", 0, "", 0),

      // 11
      scene("The ground beneath them rips away like aluminium foil, they "
            "fall "
            "through multiple more floors all ripping away",
            "...", 12, "", 0, "", 0, "", 0),

      // 12
      scene(fella_string + " wakes up in a long thin hallway", "Get up", 32, "",
            0, "", 0, "", 0),

      // 13
      scene(fella_string + " quickly steps into the restroom",
            "The people who entered start talking about how some of the "
            "newbies have been getting marked for 'expirey' and that in the "
            "past it just meant getting thrown onto the street, they start "
            "to "
            "open the door that " +
                fella_string + " and panick",
            16, &time_warn, "Look around", 15, "", 0, "", 0, "", 0),

      // 14  NOTE: UNUSED
      scene("", "", 0, "", 0, "", 0, "", 0),

      // 15
      scene("They see a vent and start to kick it open, after it pops off "
            "with "
            "a loud bang " +
                fella_string + " quickly jumps in...",
            fella_string +
                " is then smitted by an eletric charge, as they convulse "
                "they "
                "see on the ceiling a series of symbols... <- -> -> <- ↓",
            49, &time_warn_2, "Start crawling", 19, "", 0, "", 0, "", 0),

      // 16
      scene(fella_string +
                " is then slapped, punched and thrown around for a bit",
            "wake up", 17, "", 0, "", 0, "", 0),

      // 17
      scene(fella_string + " is casted onto the street, and limps away...", "",
            0, "", 0, "", 0, "", 0, &player_has_won),

      // 18
      scene("Another split...", "They sit still...", 48, "Go left", 48,
            "Go straight", 48, "Go right", 48, "", 0),

      // 19
      scene(fella_string +
                " starts to akwarding shuffle and soon finds a split",
            "Go left", 20, "Go right", 18, "", 0, "", 0),

      // 20
      scene(fella_string + "hears people below...", "They sit still...", 48,
            "Go straight", 48, "Go right", 21, "", 0, "", 0),

      // 21
      scene("A rat scurries by...", "They sit still...", 48, "Go left", 22,
            "Go straight", 48, "Go right", 23, "", 0),

      // 22
      scene("The dirty, stlightly rusted sheet metal vents slowly start to "
            "turn "
            "silver, and the the words FLUMMOXX are embossed on every "
            "surface...",
            "They sit still...", 48, "Go left", 48, "Go straight", 29, "", 0,
            "", 0),

      // 23
      scene("They round the corner, only to see another corner",
            "They sit still...", 48, "Go left", 23, "", 0, "", 0, "", 0),

      // 24  NOTE: Unused
      scene("", "", 0, "", 0, "", 0, "", 0),

      // 25
      scene("As they finish that corner, they now see a new split, then " +
                fella_string +
                " hears wispers, and feels pricks on the back of their neck, "
                "something compels them to go right...",
            "Go down", 27, "Go straight", 48, "Go right", 26, "", 0),

      // 26
      scene("The sound of rain starts to get closer and " + fella_string +
                " feels a cold breeze, with a glint of light at the end...",
            "Go back", 25, "Continue forward", 47, "", 0, "", 0),

      // 27
      scene("Lying in the vent is a small... thing? its form changes "
            "constantly but something tells " +
                fella_string + " it's what was wispering...",
            "The thing starts to move more violently, making an awful noise "
            "and eventually grinding sound as it soon disappears, at the "
            "same "
            "time the walls of the vents all turn to silver",
            29, "Grab it", 28, "Leave it", 30, "", 0, "", 0, &print_object),

      // 28
      scene(fella_string +
                "reaches out for it, the pricking sensation for earlier gets "
                "stronger but after grabbing the object, it stops spinning "
                "and "
                "doing the weird pricking thing... " +
                fella_string +
                "is relieved, but now notices the vents are silver",
            "Continue forward", 29, "", 0, "", 0, "", 0, &get_object),

      // 29
      scene("The metal suddenly gives out, " + fella_string +
                " starts to fall, eventually hitting something solid...",
            "wake up", 12, "", 0, "", 0, "", 0),

      // 30
      scene(fella_string +
                " hears a popping noise, as their legs start to feel "
                "fuzzy they pass out",
            "wake up", 31, "", 0, "", 0, "", 0, &get_mls),

      // 31
      scene(fella_string +
                " wakes up in a long but thin hallway, as they try to "
                "stand up "
                "they trip over something metal. As they come to they see "
                "strange metal prosthetics replacing what used to be their "
                "legs",
            "Get up", 32, "", 0, "", 0, "", 0),

      // 32
      scene("The hall starts to get longer, " + fella_string +
                " hears a loud crashing noise behind them",
            "", 49, "Run", 35, "Lie down", 0, "", 0, "", 0),

      // 33
      scene("They hear it, but after turning around they can't see it...",
            "Suddenly what feels like a wave pushes them off their feet", 38,
            "?", 34, "?", 34, "?", 34, "?", 34),

      // 34
      scene("The walls start to fall away, and soon so does the floor as it "
            "turns into a thick liquid, " +
                fella_string + " struggles but soon passes out.",
            "wake up", 12, "", 0, "", 0, "", 0),
      // 35
      scene(fella_string + " starts to run", "Turn around", 37, "Continue", 36,
            "", 0, "", 0),

      // 36
      scene(fella_string +
                " sees the walls start to silver over again, and "
                "dives for the end of the hall, there is a flash of white "
                "and "
                "yet again they pass out, god this trope is getting anoyying",
            "wake up (for like the 5th time)", 17, "", 0, "", 0, "", 0),

      // 37
      scene("The wall closes in", "Turn around", 33, "", 0, "", 0, "", 0),

      // 38
      scene(fella_string + " starts to feel a somewhat fuzzy feeling all "
                           "over their body",
            "", 0, "", 0, "", 0, "", 0),

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
      scene(fella_string +
                " gets to a vent, kicks it open and falls onto a street",
            "look up", 17, "", 0, "", 0, "", 0),

      // 48
      scene(fella_string +
                " starts to feel the electricty build, they are then zapped",
            "", 0, "", 0, "", 0, "", 0, &player_is_kill),
      // 49
      scene(fella_string + " is dead.", "", 0, "", 0, "", 0, "", 0,
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

    // God this is cursed
    if (scene_index == 38) {
      final_check();
    }

    if (scene_index == 35) {
      mls_check();
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
