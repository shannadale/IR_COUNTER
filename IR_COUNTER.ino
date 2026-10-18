/*====================================================
             IR SENSOR OBJECT COUNTER
======================================================
Description:
  Counts objects detected by an IR sensor and displays
  the count on two seven-segment displays and Serial Monitor.

Programmer:
  De Asis, Felicity M.
  Dela Torre, Shanna Dale R.
  Galpo, Rhile L.

Date:
  15 October 2026
------------------------------------------------------*/

#include "decoder.h"

// GPIOS
const uint8_t IR = 36;

int counter = 0;
int input = HIGH;
int previousInput = HIGH;

void setup() {

  // IR SENSOR
  pinMode(IR, INPUT);

  // SEVEN-SEGMENT DISPLAYS
  decoderSetup();

  Serial.begin(9600);

  // INITIAL DISPLAY
  decoder(counter);

  // READ INITIAL SENSOR STATE
  previousInput = digitalRead(IR);

  // COUNT IF OBJECT IS ALREADY DETECTED AT STARTUP
  if (previousInput == LOW) {
    counter++;
    decoder(counter);
    Serial.printf("Object Count: %d\n", counter);
  }
}

void loop() {

  // READ IR SENSOR
  input = digitalRead(IR);

  // COUNT WHEN A NEW OBJECT IS DETECTED
  if (previousInput == HIGH && input == LOW) {

    counter++;

    // RESET AFTER 99
    if (counter > 99) {
      counter = 0;
    }

    // UPDATE DISPLAYS
    decoder(counter);

    // SERIAL MONITOR
    Serial.printf("Object Count: %d\n", counter);
  }

  // SAVE CURRENT SENSOR STATE
  previousInput = input;

  delay(20);
}