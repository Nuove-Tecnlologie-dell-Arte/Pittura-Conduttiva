#include <ezButton.h>

ezButton button(40);  // create ezButton object that attach to pin 7;
int ledPin = 28;
int ledPin2 = 24;
int ledState = LOW;

void setup() {
  Serial.begin(9600);
  button.setDebounceTime(50); // set debounce time to 50 milliseconds
  pinMode (ledPin, OUTPUT);
  pinMode (ledPin2, OUTPUT);
}

void loop() {
  button.loop(); // MUST call the loop() function first

  if(button.isPressed()){
        // toggle state of LED
    ledState = !ledState;

    // control LED arccoding to the toggleed sate
    digitalWrite(ledPin, ledState);
    digitalWrite(ledPin2, !ledState);
    Serial.println("premuto");
  }

}