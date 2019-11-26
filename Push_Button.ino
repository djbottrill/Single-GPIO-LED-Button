/*
  
  Single GPIO illuminated push button 
  Based on the Debounce example documented below.
  
  This simple circuit uses a single GPIO port to drive an LED in addition to 
  acting as a push button input.
  
  Most of the time the GPIO is configrured an Open Drain output driving the LED
  periodically it is switched to an input and the button state is read.
  
  Note:
  Whilst the button is pressed the LED will light as it is being turned on by the push button
  so if the button press is to turn the LED off the it will not actually go off until the 
  push button is released, in practice this is not an esthetic problem.
   
  It is recomended that GPIO used is 5V tollerant however in practive leakage is low and
  in practice reaches less than 3V.

  Each time the input pin goes from High to LOW  (e.g. because of a push-button
  press), the led state is toggled. There's a minimum delay between toggles to 
  debounce the circuit (i.e. to ignore noise).

  The circuit:
  - LED is attached from 5V to GPIO pin via a suitable resistor 
    (suggested 330 ohm for white LED) check the GPIO mA sink rating for your MCU.
    Older Gallium Arsenide LEDs could be driven from 3.3V.
  - pushbutton attached from GPIO pin to ground 

  Danger:
  This will only work on MCUs that support Open Drain outputs such as the STM32 and SAMD21
  as the push button grounds the GPIO pin when pressed other MCUs such as the ATMEGA328P 
  could be damaged if wired this way.
  Please observe the maximum sink current of your MCU if you are driving a number of LEDs.   
 
  26 November 2019 - David Bottrill


  Baed on Debounce
  created 21 Nov 2006
  by David A. Mellis
  modified 30 Aug 2011
  by Limor Fried
  modified 28 Dec 2012
  by Mike Walters
  modified 30 Aug 2016
  by Arturo Guadalupi

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Debounce
*/

// constants won't change. They're used here to set pin numbers:
const int buttonPin = PB5;   // the number of the pushbutton / LED pin

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = HIGH;  // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  // Nothing to do here
}

void loop() {
  pinMode(buttonPin, INPUT);              // Set button as input
  //pinMode(buttonPin, INPUT_PULLUP);     // Pullup may be required if running from 3.3V
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin); 
  pinMode(buttonPin, OUTPUT_OPEN_DRAIN);  // Switch the GPIO pin to Open Drain output
  digitalWrite(buttonPin, ledState);      // and restore LED state
  delay(1);                               // Short delay to ensure the GPIO is in output mode long enough
  
  // check to see if you just pressed the button
  // (i.e. the input went from High to LOW), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is LOW (Pressed)
      if (buttonState == LOW) {
        ledState = !ledState;             // LED will be updated on the next program loop
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
