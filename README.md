# Single-GPIO-LED-Button

Single GPIO illuminated push button 
Based on the Debounce example documented below.
  
This simple circuit uses a single GPIO port to drive an LED in addition to acting as a push button input.
  
Most of the time the GPIO is configured as an Open Drain output driving the LED, periodically it is switched to an input and the button state is read.
  
Note:

Whilst the button is pressed the LED will light as it is being turned on by the push button so if the button press is to turn  the LED off the it will not actually go off until the push button is released, in practice this is not an esthetic problem.
   
It is recomended that GPIO used is 5V tollerant however in practice leakage is low and is less than 3V.

Each time the input pin goes from High to LOW  (e.g. because of a push-button press), the led state is toggled. There's a minimum delay between toggles to debounce the circuit (i.e. to ignore noise).

The circuit:

- LED is attached from 5V to GPIO pin via a suitable resistor 
    (suggested 330 ohm for white LED) check the GPIO mA sink rating for your MCU.
    Older Gallium Arsenide LEDs could be driven from 3.3V.
- pushbutton attached from GPIO pin to ground 

Danger:

This will only work on MCUs that support Open Drain outputs such as the STM32 and SAMD21 as the push button grounds the GPIO pin when pressed, other MCUs such as the ATMEGA328P could be damaged if wired this way.
Please observe the maximum sink current of your MCU if you are driving a number of LEDs.   
 
26 November 2019 - David Bottrill


Based on Debounce

created 21 Nov 2006 by David A. Mellis
modified 30 Aug 201 by Limor Fried
modified 28 Dec 2012 by Mike Walters
modified 30 Aug 2016 by Arturo Guadalupi

This example code is in the public domain.

http://www.arduino.cc/en/Tutorial/Debounce
