/*
  The MIDI message consists of three bytes, first setting the status
  of the message, and the following bytes denoting the action, which
  note number, velocity, pressure etc. The data bytes are different
  depending on the type of the message set by the status byte.

  Refer to the following chart for which bytes do what:

  https://www.midi.org/specifications-old/item/table-2-expanded-messages-list-status-bytes
*/

void MIDImessage(byte status, byte data1, byte data2)
{
  Serial.write(status);
  Serial.write(data1);
  Serial.write(data2);
}
