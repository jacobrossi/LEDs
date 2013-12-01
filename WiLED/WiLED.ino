#define FORCE_SOFTWARE_SPI
#define FORCE_SOFTWARE_PINS
#include "FastSPI_LED2.h"

///////////////////////////////////////////////////////////////////////////////////////////
//
//  Drives RGB lED strands based on packets received via XBee wireless
//  Protocol is #IHSL where 
//      # is a delimeter
//      I is a byte indicating the LED index
//      H, S, and L are each bytes indicating hue, saturation, and luminosity respectively

// How many leds are in the strip?
#define NUM_LEDS 120

// Data pin that led data will be written out over
#define DATA_PIN 7

// This is an array of leds.  One item for each led in the strip.
CRGB leds[NUM_LEDS];

// Data read from XBee
int serialData = 0;

void setup() {
      	// sanity check delay - allows reprogramming if accidently blowing power w/leds
       	delay(2000);
       
       // Set up the leds and tell the controller about them
       FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
       
       // Start up serial comm with XBee
      Serial.begin(9600);
}

//Primary driver loop
void loop() {
  
  if(Serial.available() > 0){
      //Read first byte  
      myData = Serial.read();
      //
            
      // Update LEDs
     // leds[ledIndex].setHSV(hue,255,128); //= CRGB::White;
      // Show the leds (only one of which is set to white, from above)
      //FastLED.show();
   }
}


