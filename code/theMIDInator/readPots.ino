/*
  Because potentiometers, especially cheaper potentiometers,
  oftentimes can have a little bit of jitter, they may
  quickly switch between two adjacent values. Some care need
  to be taken to make sure to stabilize the values so not
  to constantly send MIDI messages, flooding communications
  and slowing down the program.
*/

void readPots() {

  int diff = 4; // difference amount

  // READ POTENTIOMETERS //
  
  potVal1 = analogRead(pot1);
  potVal2 = analogRead(pot2);
  potVal3 = analogRead(pot3);
  slidePotVal = analogRead(slidePot);

  // CALCULATE DIFFERENCE BETWEEN NEW VALUE AND LAST RECORDED VALUE //
  
  int potVal1diff = potVal1 - lastPotVal1;
  int potVal2diff = potVal2 - lastPotVal2;
  int potVal3diff = potVal3 - lastPotVal3;
  int slidePotValdiff = slidePotVal - lastSlidePotVal;

  // SEND MIDI MESSAGE //
  
  if (abs(potVal1diff) > diff) // execute only if new and old values differ enough
  {
    MIDImessage(177, 0, map(potVal1, 0, 1023, 0, 127)); // map sensor range to MIDI range
    lastPotVal1 = potVal1; // reset old value with new reading
  }

  if (abs(potVal2diff) > diff)
  {
    MIDImessage(177, 1, map(potVal2, 0, 1023, 0, 127));
    lastPotVal2 = potVal2;
  }

  if (abs(potVal3diff) > diff)
  {
    MIDImessage(177, 2, map(potVal3, 0, 1023, 0, 127));
    lastPotVal3 = potVal3;
  }

  if (abs(slidePotValdiff) > diff)
  {
    MIDImessage(177, 3, map(slidePotVal, 1023, 0, 0, 127));
    lastSlidePotVal = slidePotVal;
  }

  delay(2); // small delay further stabilizes sensor readings

}

