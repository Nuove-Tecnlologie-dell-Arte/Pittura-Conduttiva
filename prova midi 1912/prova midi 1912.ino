// include MIDI library
#include <MIDI.h>
#include <ezButton.h>

MIDI_CREATE_DEFAULT_INSTANCE();

byte noteByte; //Note to send to application
byte velocityByte; //Speed of buttonpress (used in midi buttons capable of measuring force) In regular buttons this is the max MIDI value.

// Set pin number for variable
ezButton button(40);

// Set state of button to unpressed
int buttonState2 = 0;

// This variable prevents a button from being pressed more than once per press (a button might send a signal multiple times when being pressed)
int note2 = 0;

void setup() {
  MIDI.begin();
  // 115200 Hairless MIDI Serial Bridge baud rate
  Serial.begin(115200);

  Serial.begin(9600);
  button.setDebounceTime(50);
}

void loop() {
  button.loop();

  // Read state of button (is it pressed?)
  //This delay is required to prevent a failure of "MIDI.sendControlChange"

  // Button 2

  // When button pressed:
  if (buttonState2 == HIGH) {
  // If note is not playing (first time recieving a button press signal)
    if (note2 == 0) {

    // Play note (note number, velocity, channel)
    // more info: Arduino MIDI Library: MIDI_Class Class Reference 1
    // MIDI notes chart http://www.phys.unsw.edu.au/jw/notes.html

    // Play note 55 = G3, 127 = trigger note with max volume
    MIDI.sendNoteOn(55, 127, 1);

    // Note is now playing (Set note to 1, so that this function can not reactivate while keeping the button pressed)
    note2 = 1;
    }
    // When the button is released
  } else {
    // If the note is playing
    if (note2 == 1) {
      // Stop playing the note
      MIDI.sendNoteOff(55, 0, 1);
    }
    // Set note back to 0 so you can reactivate it
  note2 = 0;
  }

  delay(1); // Delay to keep everything working smoothly

}