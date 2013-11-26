#define FORCE_SOFTWARE_SPI
#define FORCE_SOFTWARE_PINS
#include "FastSPI_LED2.h"

///////////////////////////////////////////////////////////////////////////////////////////
//
// Move a white dot along the strip of leds.  This program simply shows how to configure the leds,
// and then how to turn a single pixel white and then off, moving down the line of pixels.
// 

// How many leds are in the strip?
#define NUM_LEDS 120

// Data pin that led data will be written out over
#define DATA_PIN 7

// Clock pin only needed for SPI based chipsets when not using hardware SPI
//#define CLOCK_PIN 8

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];
int hue;

// This function sets up the ledsand tells the controller about them
void setup() {
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
 	delay(2000);
       FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
       hue = 0;
}
// This function runs over and over, and is where you do the magic to light
// your leds.
void loop() {
   // Move a single white led 

   for(int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex = ledIndex + 1) {
      // Turn our current led on to white, then show the leds
      leds[ledIndex].setHSV(hue,255,128); //= CRGB::White;

      // Show the leds (only one of which is set to white, from above)
      FastLED.show();

      // Wait a little bit
      delay(100);

      // Turn our current led back to black for the next loop around
      leds[ledIndex] = CRGB::Black;
      
      hue = hue + 1;
      if(hue > 255) {
        hue = 0;
      }
   }
}


