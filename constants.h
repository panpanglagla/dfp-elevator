#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <Arduino.h>

const byte DF_PLAYER_ATTEMPTS = 10;

const byte VOLUME_START = 16;
const byte VOLUME_MIN = 0;
const byte VOLUME_MAX = 20;

const long unsigned DURATION = 20000;
const long unsigned G_DURATION = 1000;

const int LOOP_DELAY = 50;

const byte PIN_RX = 10;
const byte PIN_TX = 11;

const float ACC_GZ_THRESHOLD = 0.02;
const float ACC_GZ_BASE = 1.02;

#endif
