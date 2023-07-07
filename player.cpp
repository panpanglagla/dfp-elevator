#include "player.h"

boolean _printDetails = false;

Player::Player() {
  _current = 1;
  _numFiles = 0;
} 

void Player::connect(DFRobotDFPlayerMini player) {
  _volume = VOLUME_START;
  _player = player;
  _player.setTimeOut(500);
  _player.volume(_volume);
  _numFiles = _player.readFileCounts();
}
byte Player::getVolume() {
  return _volume;
}

boolean Player::setVolume(byte volume) {
  if (volume > VOLUME_MAX || volume < VOLUME_MIN) {
    _volume = volume;
    return false;
  }
  _player.volume(_volume);
  return true;
}

boolean Player::isPlaying() {
  return _isPlaying;
}

void Player::start() {
  if (_current < _numFiles) {
    _current++;
  } else {
    _current = 1;
  }
  _player.playFolder( 1, _current);
}

void Player::pause() {
  _player.pause();
}

void Player::stop() {
  _player.stop();
}
