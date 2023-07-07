#ifndef PLAYER_H
#define PLAYER_H
#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include "constants.h"

class Player
{
  private:
    DFRobotDFPlayerMini _player;
    byte _volume = VOLUME_START;
    boolean _isPlaying = false;
    boolean _isSwitching = false;
    boolean _canSwitch = false;
    int _current = 1;
    int _numFiles;
    void printDetail(uint8_t type, int value);

  public:
    Player();
    void connect(DFRobotDFPlayerMini player);
    boolean isPlaying();
    byte getVolume();
    boolean setVolume(byte volume);
    void start();
    void update();
    void pause();
    void stop();
};

#endif