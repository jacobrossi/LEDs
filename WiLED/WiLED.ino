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
// this is where we will put our data
int myData = 0;

// This function sets up the ledsand tells the controller about them
void setup() {
      	// sanity check delay - allows reprogramming if accidently blowing power w/leds
       	delay(2000);
       FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
       
       // Start up our serial port, we configured our XBEE devices for 38400 bps. 
      Serial.begin(9600);
}
// This function runs over and over, and is where you do the magic to light
// your leds.
void loop() {
  
  if(Serial.available() > 0){
        myData = Serial.read();
        if(myData == '\n')
            Serial.write(myData);
        else
            Serial.write(myData + 1);
            
      // Update LEDs
     // leds[ledIndex].setHSV(hue,255,128); //= CRGB::White;
      // Show the leds (only one of which is set to white, from above)
      //FastLED.show();
   }
}


