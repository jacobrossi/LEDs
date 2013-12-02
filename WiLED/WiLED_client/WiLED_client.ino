#define FORCE_SOFTWARE_SPI
#define FORCE_SOFTWARE_PINS
#include "FastSPI_LED2.h"

///////////////////////////////////////////////////////////////////////////////////////////
//
//  Drives RGB lED strands based on packets received via XBee wireless
//  Protocol:  IIIRRRGGGBBB#
//  where,  III is 3-digit LED index
//          RRR is 3-digit RED value
//          GGG is 3-digit GREEN value
//          BBB is 3-digit BLUE value
//

// How many leds are in the strip?
#define NUM_LEDS 120

// Data pin that led data will be written out over
#define DATA_PIN 7

// Array of leds
CRGB leds[NUM_LEDS];

// Data packet from WiLED server (initialized to LED #0 white)
char rawData[] = "000255255255#";
String data = "000255255255#";
int ledIndex = 0;
int ledRed = 255;
int ledGreen = 255;
int ledBlue = 255;

void setup() {
      	// sanity check delay - allows reprogramming if accidently blowing power w/leds
       	delay(2000);
       
       // Set up the leds and tell the controller about them
       FastLED.addLeds<WS2811, DATA_PIN, BRG>(leds, NUM_LEDS);
       
       // Start up serial comm with XBee
      Serial.begin(9600);
}

//Primary driver loop
void loop() {
  
  if(Serial.available() >= 13){
 
      //Read packet from server 
      Serial.readBytesUntil('#',rawData,14);
      data = String(rawData);
      //Serial.println(data);
      
      //Validate packet
      if(data.length() == 13 && data.indexOf('#') == 12) {
        //Parse packet
        ledIndex = data.substring(0,3).toInt();
        ledRed = data.substring(3,6).toInt();
        ledGreen = data.substring(6,9).toInt();
        ledBlue = data.substring(9,12).toInt();

        /*Serial.println(ledIndex);
        Serial.println(ledRed);
        Serial.println(ledGreen);
        Serial.println(ledBlue);*/
        
        //Update LEDs
        leds[ledIndex].setRGB(ledRed, ledGreen, ledBlue);
        FastLED.show(); 
      }
   }
}


