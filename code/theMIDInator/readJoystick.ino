/*
  The joystick is essentially two potentiometers, one
  in each direction. Due to their limited movement
  range and low range of resistance we are only
  reading a part of their range (~380-640) and
  therefore we have to map our output accordingly.
  Unfortunately that also means that the joystick
  will not have as high of a fidelity as a full range
  10kOhm resistor, like we use elsewhere in The
  MIDInator, would have.

  It is also possible to turn off one or both axis of
  the joystick using the two toggle switches under the
  joystick.

  Because we are using the Y axis of the joystick to
  send a modulation MIDI message, like the modulation
  wheel you would find on many MIDI keyboards, some
  additional value splitting has to be done to be
  able to send a 14 bit value in two chunks.

  Because of inherent jitteryness of some potentiometers
  a 'difference' value is set up and checked. Events
  will only trigger if the value of the last recorded
  reading is higher than this value. Set to '1' if your
  potentiometer is very steady. A value of '2' will
  stop it from jittering between two adjacent numbers.
  If your potentiometer is very noisy a higher value
  may be required. Keep in mind that higher difference
  values will result in further less fidelity of the
  potentiometer reading.
*/

void readJoystick() {

  int diff = 2;

  // READ LEFT-RIGHT //
  if (digitalRead(Xswitch) == 0) { // execute only if X-switch is turned on

    joyXval = analogRead(joyX);
    int joyXvalDiff = joyXval - lastJoyXval;

    if (abs(joyXvalDiff) > diff) // send MIDI message only if new and old values differ enough
    {
      MIDImessage(176, 1,  map(joyXval, 379, 637, 127, 0)); // map sensor range to MIDI range

      lastJoyXval = joyXval; // reset old value with new reading
    }
    delay(2); // for stability
  }


  // READ UP-DOWN FOR MODULATION //
  if (digitalRead(Yswitch) == 0) {

    joyYval = analogRead(joyY);
    int joyYvalDiff = joyYval - lastJoyYval;

    if (abs(joyYvalDiff) > diff)
    {
      // construct 14 bit modulation value and send over MIDI
      int modulation = map(joyYval, 361, 635, -8000, 8000);
      unsigned int change = 0x2000 + modulation;  //  0x2000 == no Change
      unsigned char low = change & 0x7F;  // low 7 bits
      unsigned char high = (change >> 7) & 0x7F;  // high 7 bits

      MIDImessage(224, low, high);

      lastJoyYval = joyYval;
    }
    delay(2);
  }

}

