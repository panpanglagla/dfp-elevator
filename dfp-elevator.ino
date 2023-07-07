#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include "SoftwareSerial.h"
#include "Arduino_LSM6DS3.h"
#include "constants.h"
#include "player.h"

static unsigned long timer = 0;
static unsigned long timerTrigger = 0;
static unsigned long timerPlaying = 0;


Player player;
DFRobotDFPlayerMini dfPlayer;
SoftwareSerial mySerial(PIN_RX, PIN_TX);
typedef enum {
  Idle,
  Playing
} stateType;
stateType state = Idle;
byte i = 0;
float x, y, z;
boolean usePlayer = true;
boolean isUnderThreshold = true;
boolean belowThreshold = false;
boolean aboveThreshold = false;

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);

  for (i = 0; i < DF_PLAYER_ATTEMPTS; i++) {
    delay(500);
    if (dfPlayer.begin(mySerial)) {
      break;
    }
    if (i == DF_PLAYER_ATTEMPTS - 1) {
      usePlayer = false;
    }
  }
  if (usePlayer) {
    player.connect(dfPlayer);
  }

  while (!Serial);

  if (!IMU.begin()) {
    while (1);
  }
}

void loop() {
  timer = millis();
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
    /*
      // Serial Plotter
      // Test in order to define ACC_GZ_THRESHOLD and ACC_GZ_BASE
      Serial.print("z:");
      Serial.println(z);
    */
  }

  if (z > ACC_GZ_BASE - ACC_GZ_THRESHOLD && z < ACC_GZ_BASE + ACC_GZ_THRESHOLD) {
    timerTrigger = 0;
    isUnderThreshold = true;
    aboveThreshold = false;
    belowThreshold = false;
  } else {
    if (isUnderThreshold) {
      timerTrigger = millis();
    }
    isUnderThreshold = false;
    if (z < ACC_GZ_BASE) {
      if (!belowThreshold) {
        timerTrigger = millis();
      }
      aboveThreshold = false;
      belowThreshold = true;
    } else {
      if (!aboveThreshold) {
        timerTrigger = millis();
      }
      aboveThreshold = true;
      belowThreshold = false;
    }
  }

  switch (state) {
    case Idle:
      if (!isUnderThreshold) {
        if (timerTrigger > 0 && timerTrigger < timer && timer - timerTrigger > G_DURATION) {
          if(usePlayer) {
            player.start();
          }
          timerTrigger = 0;
          timerPlaying = millis();
          state = Playing;
        }
      }
      break;
    case Playing:
      if (!isUnderThreshold) {
        if (timerTrigger > 0 && timerTrigger < timer && timer - timerTrigger > G_DURATION) {
          timerPlaying = millis();
        }
      }
      if (timerPlaying > 0 && timerPlaying < timer && timer - timerPlaying > DURATION) {
        if(usePlayer) {
          player.pause();
        }
        timerTrigger = 0;
        timerPlaying = 0;
        state = Idle;
      }
      break;
  }


  delay(LOOP_DELAY);
}