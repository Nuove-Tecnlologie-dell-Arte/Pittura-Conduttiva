// include MIDI library
#include <MIDI.h>
#include <ezButton.h>

byte noteByte;  //Note to send to application
byte velocityByte; //Speed of buttonpress (used in midi buttons capable of measuring force) In regular buttons this is the max MIDI value.


// Set pin number for variable
ezButton button(40);



// This variable prevents a button from being pressed more than once per press (a button might send a signal multiple times when being pressed)
int note2 = 0;


// set analog values to 0
int analogValue_1 = 0;
int analogValue_2 = 0;

// Maximum MIDI value is 127. To notice change, even if first value is 127, the last value is set to 128
int lastanalogValue_1 = 128;
int lastanalogValue_2 = 128;


void setup() {
  MIDI.begin();
  // 115200 Hairless MIDI Serial Bridge baud rate
  Serial.begin(115200);
  button.setDebounceTime(50);
  pinMode(button, INPUT);


}

void loop() {
  // Read state of button (is it pressed?)
  int button = digitalRead(button);


  delay(1); //This delay is required to prevent a failure of "MIDI.sendControlChange"

  // Analog potentiometer

  // Potentiometer gives values up to 1023. MIDI signal ranges from 0 to 127, therefor we devide by 8.

  int analogValue_1 = analogRead(A0) / 8;
  int analogValue_2 = analogRead(A1) / 8;


  // Potentiometer could be too sensitive and give different (+-1) values.
  // Check if the last value is more than this minor fluctuation, if so send the signal.
  if ((analogValue_1 - lastanalogValue_1) > 1 || (analogValue_1 - lastanalogValue_1) < -1) {
    // Has the value changed?
    if (analogValue_1 != lastanalogValue_1) {

      // More info: http://arduinomidilib.sourceforge.net/a00001.html
      // Send serial value (ControlNumber 1, ControlValue = analogValue_1, Channel 1)
      MIDI.sendControlChange(1, analogValue_1, 1);

      lastanalogValue_1 = analogValue_1; //Set the current value as the last value
    }
  }

  if ((analogValue_2 - lastanalogValue_2) > 1 || (analogValue_2 - lastanalogValue_2) < -1) {
    // Has the value changed?
    if (analogValue_2 != lastanalogValue_2) {
      MIDI.sendControlChange(2, analogValue_2, 1);
      lastanalogValue_2 = analogValue_2;
    }
  }


  // Button 2

  // When button pressed:
  if (button == HIGH) {
    // If note is not playing (first time recieving a button press signal)
    if (note2 == 0) {

      // Play note (note number, velocity, channel)
      // more info: http://arduinomidilib.sourceforge.net/a00001.html
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