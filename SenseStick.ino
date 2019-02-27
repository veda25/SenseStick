/*
 * Creation & Computation - Digital Futures, OCAD University
 * Kate Hartman / Nick Puckett
 * 
 * Read an Ultrasonic Proximity Sensor using the NewPing Library 
 * To install go to "Tools" -> "Manage Libraries" and search for "NewPing"
 * print the value to Serial and scale it using a timer
 * 
 * 
 */
#include <Wire.h>
#include "Adafruit_DRV2605.h"
#include <NewPing.h>   //include the library

Adafruit_DRV2605 drv; //add Driver

int effect; //initializing all effects
int effect2;
int effect3;
int effect4;
int effect5;
int effect6;

int triggerPin = 4;   //pin conneccted to the Trig pin on the sensor
int echoPin = 5;       //pin connected to the Echo pin on the sensor
int maxDistance = 200;  //set the max distance for the sensor to read (helps with errors)
int distanceVal;        //variable to hold the distance val

int sampleRate = 200;   //how fast to sample the value
long lastReading;       //used for the timer

NewPing proximity1(triggerPin, echoPin, maxDistance);   //sets up the sensor object

void setup() 
{
  Serial.begin(9600);  //start the serial port
    drv.begin();

      drv.selectLibrary(1);
  
  // I2C trigger by sending 'go' command 
  // default, internal trigger when sending GO command
  drv.setMode(DRV2605_MODE_INTTRIG); 
}

void loop() 
{

  if(millis()-lastReading>=sampleRate) //this very simple statement is the timer,
  { 
  distanceVal = proximity1.ping_cm();  //get the distance value in centimeters

  
  lastReading = millis();


  Serial.print("Distance Reading CM : ");  //print the value to the Serial monitor
  Serial.println(distanceVal);

  if (distanceVal <= 10) {
         Serial.print("Effect #"); Serial.println(effect); // when obstacle is too close, simply pulse
  // set the effect to play
  drv.setWaveform(0, effect);  // play effect 
  drv.go();
    delay(1000);
  
  }
  
  
  else if (distanceVal <= 30 ) {
      Serial.print("Effect #"); Serial.println(effect2); // critical alert to step over obstacle immediately
  // set the effect to play
  drv.setWaveform(0, effect2);  // play effect 
  drv.go();
    delay(1000);
    
    }
    
  else if (distanceVal <= 45) {
      Serial.print("Effect #");Serial.println(effect3); // warning for obstacle proximity
  drv.setWaveform(0, effect3);  // play effect 
  drv.go();
      delay(1000);
  
    }
    
  else if (distanceVal <= 60) {
    
  Serial.print("Effect #");Serial.println(effect4); // intimate obstacle presence
  drv.setWaveform(0, effect4);  // play effect 
  drv.go();
      delay(1000);
    
    }


  else if (distanceVal <= 90){

      Serial.print("Effect #");Serial.println(effect5); // intimate any possible obstacles in the distance
  drv.setWaveform(0, effect5);  // play effect 
  drv.go();
      delay(1000);

  }
 
  else if (distanceVal <= 200){

      Serial.print("Effect #");Serial.println(effect6); // pulsate to indicate that the device is on and working
  drv.setWaveform(0, effect6);  // play effect 
  drv.go();
      delay(1000);
    
    
   
    }

  
effect = 6;  // all effect serial numbers from driver library
effect2 = 47;
effect3 = 48;
effect4 = 49;
effect5 = 50;
effect6 = 51;

    
  }

  
}
