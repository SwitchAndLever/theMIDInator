// THE MIDINATOR //

// Author: Daniel Jansson // Switch & Lever // switchandlever.com

// This code is a companion to the YouTube video on how to build a MIDI controller (called
// The MIDInator) linked below:

// YOUTUBE LINK

// The MIDInator uses an Arduino MEGA 2560, connected to a keypad, a few potentiometers, rotary
// encoders, switches and a joystick to send MIDI messages over USB serial to a Serial to
// MIDI bridge software running on the computer.

// COMPONENT LIST

// 1x   Arduino MEGA 2560
// 3x   10kOhm (B10K) linear rotary potentiometer
// 1x   10kOhm (B10K) linear slide potentiometer
// 1x   ALPS 6 position rotary switch (SRBM160700)
// 2x   ALPHA 12 step rotary encoder (RE130F-41-175F-12P)
// 1x   phone keypad from old Ericsson Diavox
// 2x   generic slide toggle switches
// 1x   generic (ON)-OFF-(ON) toggle switch
// 1x   remote control joystick (2 potentiometers)

// The libraries used in this sketch can be found at:

// Keypad.h :: https://github.com/Chris--A/Keypad
// Encoder.h :: https://github.com/PaulStoffregen/Encoder

// Please refer to the documentation for the individual libraries on their respective
// operation and function.

// This code is licensed under a GNU General Public License and may be freely modified
// and redistributed under the same license terms.
// https://www.gnu.org/licenses/gpl-3.0.en.html


// KEYPAD //

#include <Keypad.h>

const byte ROWS = 4; // four rows
const byte COLS = 3; // three columns
char keys[ROWS][COLS] = {  // keypad keys, 1-9, 0, S for star (asterisk) and P for pound (square)
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'S', '0', 'P'}
};

byte rowPins[ROWS] = {43, 41, 39, 35}; // keypad row pinouts
byte colPins[COLS] = {33, 31, 37}; // keypad column pinouts

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int midC = 60; // MIDI note value for middle C on a standard keyboard

const int transposePin1 = 22; // pins for the switch controlling transposing
const int transposePin2 = 23;
int transpose = 0;  // if = 0 no transposing
int transposeLeft = 0;
int transposeRight = 0;
int oldTransposeLeft = 0;
int oldTransposeRight = 0;
unsigned long transposeTimer = 0;  // for debouncing


// ROTARY ENCODER //

#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>

Encoder myEnc1(26, 27);
Encoder myEnc2(24, 25);
long position1  = -999;
long position2  = -999;
int encVals[12] = {64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64}; // set initial value of encoder to mid range of 0-127


// ROTARY SWITCH //

const int rotSwitch1 = 30;  // rotary switch pins
const int rotSwitch2 = 32;
const int rotSwitch3 = 34;
const int rotSwitch4 = 36;
const int rotSwitch5 = 38;
const int rotSwitch6 = 40;
int cVal = 1;


// POTENTIOMETERS //

const int pot1 = A0;  // potentiometer pins
const int pot2 = A1;
const int pot3 = A2;
const int slidePot = A3;

int potVal1 = 0;
int potVal2 = 0;
int potVal3 = 0;
int slidePotVal = 0;

int lastPotVal1 = 0;
int lastPotVal2 = 0;
int lastPotVal3 = 0;
int lastSlidePotVal = 0;


// JOYSTICK //

const int joyX = A5;  // joystick pins
const int joyY = A4;

const int Xswitch = 52;  // axis switche pins
const int Yswitch = 50;

int joyXval = 0;
int joyYval = 0;
int lastJoyXval = 0;
int lastJoyYval = 0;


void setup() {

  Serial.begin(9600); // enable serial communication

  pinMode(transposePin1, INPUT_PULLUP);  // activate the input pullup resistor on all buttons/switches
  pinMode(transposePin2, INPUT_PULLUP);  // means you won't need external resistors to read the buttons
  pinMode(rotSwitch1, INPUT_PULLUP);
  pinMode(rotSwitch2, INPUT_PULLUP);
  pinMode(rotSwitch3, INPUT_PULLUP);
  pinMode(rotSwitch4, INPUT_PULLUP);
  pinMode(rotSwitch5, INPUT_PULLUP);
  pinMode(rotSwitch6, INPUT_PULLUP);
  pinMode(Xswitch, INPUT_PULLUP);
  pinMode(Yswitch, INPUT_PULLUP);

}


void loop() {

  readRotSwitch();    // read roatary switch
  readEncoder();      // read roraty encoder
  readKeyPad();       // read keypad + transpose switch
  readPots();         // read potentiometers
  readJoystick();     // read joystick + on/off switches

}




