#define FORCE_SOFTWARE_SPI
#define FORCE_SOFTWARE_PINS
#include "FastSPI_LED2.h"

///////////////////////////////////////////////////////////////////////////////////////////
//
//  Drives RGB lED strands based on packets received via XBee wireless
//  Protocol is 0IHSL where 
//      0 is a delimeter byte (allows packet error correction/sync) of value 0
//      I is a byte indicating the LED index
//      H, S, and L are each bytes indicating hue, saturation, and luminosity respectively
//      NOTE: I, H, S, and L may not be of value 0 as this is reserved for the delimeter 

// How many leds are in the strip?
#define NUM_LEDS 120

// Data pin that led data will be written out over
#define DATA_PIN 7

//Define constants that track each step in reading a packet
#define PACKET_WAITING 0//Waiting for start byte delimeter
#define PACKET_INDEX 1 //Next expected byte is LED index
#define PACKET_HUE 2 //Next expected byte is HUE value
#define PACKET_SATURATION 3 //Next expected byte is SATURATION value
#define PACKET_VALUE 4 //Next expected byte is VALUE (brightness)

// This is an array of leds.  One item for each led in the strip.
CRGB leds[NUM_LEDS];

// Data read from XBee
int serialData = 0;
int packetStep = PACKET_WAITING;
int ledIndex = 0;
int ledHue = 0;
int ledSat = 0;

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
      //Read byte  
      serialData = Serial.read();
      Serial.write(packetStep); //Writes back packet step value to debug protocol synchronization
      
      if(serialData == 0) {
        packetStep = PACKET_INDEX; //Packet delimeter read, reset mode to 
      }else{
        switch(packetStep) {
          case PACKET_INDEX:
            ledIndex = serialData;
            packetStep++;
            break;
          case PACKET_HUE:
            ledHue = serialData;
            packetStep++;
            break;
          case PACKET_SATURATION:
            ledSat = serialData;
            packetStep++;
            break;
          case PACKET_VALUE:
            leds[ledIndex] = CHSV(ledHue,ledSat,serialData);
            FastLED.show(); // Push to PWM   
            packetStep = PACKET_WAITING; //Reset back to wait for next packet
            break;
        }
      }
   }
}


