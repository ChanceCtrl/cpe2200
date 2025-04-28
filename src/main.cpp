#include "main.hpp"

void setup() {
  // Setup the serial port for I/O
  Serial.begin(115200);
  Serial.setTimeout(1000000);

  // Give the port sometime if stuff is being freaky
  delay(100);
}

void loop() {
  // Get the name
  Serial.print("Whats is their name?\n");
  Serial.readBytesUntil('\r', fella, sizeof(fella) - 1);
  fella[sizeof(fella) - 1] = '\0';
  string_fella = String(fella);
  Serial.println();

  // Eat spare chars
  while (Serial.available())
    Serial.read();

  Serial.print("And will " + string_fella +
               "'s escape be Hard(0) or Easy(1)?\n");
  int target_dif = Serial.parseInt();
  Serial.println();

  // Eat spare chars
  while (Serial.available())
    Serial.read();

  while (target_dif != 0 && target_dif != 1) {
    Serial.print("Please select either Hard with 0, or Easy with 1\n");
    target_dif = Serial.parseInt();
    Serial.println();

    // Eat spare chars
    while (Serial.available())
      Serial.read();
  }

  game.set_difficulty(target_dif);

  game.set_scene(1);

  while (!is_won) {
    while (Serial.available() > 0) {
      char incomingByte = Serial.read(); // Read the incoming byte

      // If it's a number, store it in the input string
      if (incomingByte >= '0' && incomingByte <= '9') {
        inputString += incomingByte; // Append the number to the string
      }

      // If Enter/Return is pressed (new line), process the input
      else if (incomingByte == '\n' || incomingByte == '\r') {
        if (inputString.length() > 0) {
          int target_option = inputString.toInt(); // Convert string to integer
          game.update(target_option); // Update the game with the input
          inputString = ""; // Clear the input string for the next input
        }
      }
    }

    game.update(long(millis() / 1000));
  }

  delay(2000);

  Serial.print("(1) Play Again?\t(0) Or not?\n");
  int try_again = Serial.parseInt();

  // Eat spare chars
  while (Serial.available())
    Serial.read();

  while (try_again != 1) {
    Serial.print("Have a good one\n");

    while (1)
      delay(100);
  }

  is_won = false;
}
