/*
  The rotary switch behaves just like any switch, it just has
  six positions rather than two or three like most switches.
  Reading the switch uses the internal pullup resistors in the
  Arduino, which means that the switch is normally HIGH when
  it's off, and normally LOW when it's on.

  The switch position is read and a value is stored in the
  cVal variable which is used by the rotary encoders to keep
  track of their values.
*/

void readRotSwitch() { // read position of rotary switch and assign it to cVal

  if (digitalRead(rotSwitch1) == LOW) { // inversed logic because of INPUT_PULLUP
    cVal = 4;
  }
  else if (digitalRead(rotSwitch2) == LOW) {
    cVal = 6;
  }
  else if (digitalRead(rotSwitch3) == LOW) {
    cVal = 8;
  }
  else if (digitalRead(rotSwitch4) == LOW) {
    cVal = 10;
  }
  else if (digitalRead(rotSwitch5) == LOW) {
    cVal = 12;
  }
  else if (digitalRead(rotSwitch6) == LOW) {
    cVal = 14;
  } else {

  }

}
