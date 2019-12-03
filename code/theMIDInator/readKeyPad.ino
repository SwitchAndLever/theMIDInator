/*
  The keypad runs on the keypad.h library, which you also can use
  to run other similar keypads with similar pinouts, or even use
  regular micro switches in an array to build your own keypad.

  With the use of a bidirectional toggle switch the keypad
  mapping can also be transposed, or moved, up and down the
  scale. The keypad starts with middle C (note number 60) on the
  Nr 1 key. Using the transpose switch moves the keypad one entire
  octave up or down, within the full range (0 - 127) of available
  notes.
*/

int kpc = 144; // the function of the keypad, 144 = Channel 1 Note on

void readKeyPad() {

  // TRANSPOSE SWITCH //

  transposeRight = digitalRead(transposePin1);

  if (oldTransposeRight != transposeRight && transposeRight == 0) { // detect switch change, and only do this once regardless how long it's held down
    if (millis() - transposeTimer > 1000) { // debounce so you can only do this once a second
      if (transpose < 48) transpose = transpose + 12; // only change transpose value if it's smaller than 48
      transposeTimer = millis();// reset debounce timer
    }
  }
  oldTransposeRight = transposeRight;

  transposeLeft = digitalRead(transposePin2);

  if (oldTransposeLeft != transposeLeft && transposeLeft == 0) { // same as above but to decrease the transpose value
    if (millis() - transposeTimer > 1000) {
      if (transpose > -60) transpose = transpose - 12; // only change transpose value if it's bigger than -60
      transposeTimer = millis();
    }
  }
  oldTransposeLeft = transposeLeft;


  // KEYPAD //

  if (kpd.getKeys())  // supports up to ten simultaneous key presses
  {
    for (int i = 0; i < LIST_MAX; i++) // scan the whole key list
    {
      if ( kpd.key[i].stateChanged)   // find keys that have changed state
      {
        if (kpd.key[i].kstate == PRESSED) // sends MIDI on message when keys are pressed
        {
          switch (kpd.key[i].kchar) {
            case '1':
              MIDImessage(kpc, midC + transpose + 0, 127);
              break;
            case '2':
              MIDImessage(kpc, midC + transpose + 1, 127);
              break;
            case '3':
              MIDImessage(kpc, midC + transpose + 2, 127);
              break;
            case '4':
              MIDImessage(kpc, midC + transpose + 3, 127);
              break;
            case '5':
              MIDImessage(kpc, midC + transpose + 4, 127);
              break;
            case '6':
              MIDImessage(kpc, midC + transpose + 5, 127);
              break;
            case '7':
              MIDImessage(kpc, midC + transpose + 6, 127);
              break;
            case '8':
              MIDImessage(kpc, midC + transpose + 7, 127);
              break;
            case '9':
              MIDImessage(kpc, midC + transpose + 8, 127);
              break;
            case 'S':
              MIDImessage(kpc, midC + transpose + 9, 127);
              break;
            case '0':
              MIDImessage(kpc, midC + transpose + 10, 127);
              break;
            case 'P':
              MIDImessage(kpc, midC + transpose + 11, 127);

          }
        }

        if (kpd.key[i].kstate == RELEASED)  // sends MIDI off message when keys are released
        {
          switch (kpd.key[i].kchar) {
            case '1':
              MIDImessage(kpc - 16, midC + transpose + 0, 0);
              break;
            case '2':
              MIDImessage(kpc - 16, midC + transpose + 1, 0);
              break;
            case '3':
              MIDImessage(kpc - 16, midC + transpose + 2, 0);
              break;
            case '4':
              MIDImessage(kpc - 16, midC + transpose + 3, 0);
              break;
            case '5':
              MIDImessage(kpc - 16, midC + transpose + 4, 0);
              break;
            case '6':
              MIDImessage(kpc - 16, midC + transpose + 5, 0);
              break;
            case '7':
              MIDImessage(kpc - 16, midC + transpose + 6, 0);
              break;
            case '8':
              MIDImessage(kpc - 16, midC + transpose + 7, 0);
              break;
            case '9':
              MIDImessage(kpc - 16, midC + transpose + 8, 0);
              break;
            case 'S':
              MIDImessage(kpc - 16, midC + transpose + 9, 0);
              break;
            case '0':
              MIDImessage(kpc - 16, midC + transpose + 10, 0);
              break;
            case 'P':
              MIDImessage(kpc - 16, midC + transpose + 11, 0);

          }
        }
      }
    }
  }
}

