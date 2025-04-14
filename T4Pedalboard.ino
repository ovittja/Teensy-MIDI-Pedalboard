// Teensy Pedalboard w/ 32 inputs (0-31) MIDI notes C2-G4
#include "MIDIcontroller.h"
#include "Bounce2.h" 

byte MIDIchannel = 5; // Set your MIDI channel here

const int numButtons = 32;
Bounce buttons[numButtons]; // Array to hold Bounce objects
const int firstNote = 36; // C2 (MIDI note #)

void setup() {
  // Initialize input pins (pullup) and attach Bounce objects
  for (int i = 0; i < numButtons; i++) {
    pinMode(i + 1, INPUT_PULLUP);
    buttons[i].attach(i + 1);
    buttons[i].interval(5); // Debounce (adjust if needed)
  }
}

void loop() {
  // Update button states
  for (int i = 0; i < numButtons; i++) {
    buttons[i].update();

    if (buttons[i].fell()) { // Note pressed
      usbMIDI.sendNoteOn(firstNote + i, 99, MIDIchannel);
    }

    if (buttons[i].rose()) { // Note released
      usbMIDI.sendNoteOff(firstNote + i, 0, MIDIchannel);
    }
  }

  // This prevents crashes that happen when incoming usbMIDI is ignored
  while (usbMIDI.read()) {}

}
