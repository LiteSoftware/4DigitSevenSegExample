/*
   Copyright 2024 udfsoft-owner

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   
   More details: https://udfsoft.com
*/

#include "SevSeg.h"

SevSeg sevseg;

bool isTimerTriger = false;

#define INITIAL_TIME 151

void setup() {
  byte numDigits = 4;
  byte digitPins[] = { 13, 12, 11, 10 };
  byte segmentPins[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
  bool resistorsOnSegments = true; // false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // COMMON_ANODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = true; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected
  
  Serial.begin(9600);

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
}

void loop() {
  static unsigned long timer = millis();
  static int deciSeconds = INITIAL_TIME;

  if (isTimerTriger){
    sevseg.setChars("OUT");
    sevseg.refreshDisplay();
    return;
  }

  if (millis() - timer >= 100) {
    timer += 100;
    deciSeconds++; // 100 milliSeconds is equal to 1 deciSecond

    if (deciSeconds <= 0) {
      isTimerTriger = true;
    }
    sevseg.setNumber(deciSeconds, 1);
  }

  sevseg.refreshDisplay();
}
