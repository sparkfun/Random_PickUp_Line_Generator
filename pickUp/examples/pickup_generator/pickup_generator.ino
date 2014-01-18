/*
Based on the following sketches:

Voice Box Demo Sketch
Written by Ryan Owens
SparkFun Electronics

PROGMEM by Arduino : http://arduino.cc/en/Reference/PROGMEM

randomSeed by Arduino: http://arduino.cc/en/Reference/randomSeed


*/

//Soft serial library used to send serial commands on pin 2 instead of regular serial pin.
#include <SoftwareSerial.h>
#include <pickuplines.h>
#include <avr/pgmspace.h>

//Define the Pin Numbers for the sketch.


#define RDY  13
#define RES  3
#define SPK  4

#define txPin  2

#define buttonPin 5
int buttonState = 0;

//Create a SoftSerial Object
SoftwareSerial speakjet = SoftwareSerial(0, txPin);

void setup()  
{
  //Configure the pins for the SpeakJet module
  pinMode(txPin, OUTPUT);
  pinMode(SPK, INPUT);
  pinMode(buttonPin, INPUT);
  
  //Set up a serial port to talk from Arduino to the SpeakJet module on pin 3.
  speakjet.begin(9600);    
  speakjet.print(20, 127); //Set the volume to the max setting 
  
  //Set up Serial communication for debugging
  Serial.begin(9600);
  
  //Configure the Ready pin as an input
  pinMode(RDY, INPUT);
  
  //Configure Reset line as an outpu
  pinMode(RES, OUTPUT);
       
  //All I/O pins are configured. Reset the SpeakJet module
  digitalWrite(RES, LOW);
  delay(100);
  digitalWrite(RES, HIGH);
  Serial.println("Reset Speakjet");
  
}

void loop()
{  

buttonState = digitalRead(buttonPin);
Serial.print("Read button state:");
Serial.println(buttonState);

if (buttonState == HIGH)
{
 randSeed(analogRead(A0));
 randNumber = random(0, 7);
 strcpy_P(buffer1, (char*) pgm_read_word(&(question_table[randNumber])));
  speakjet.print(buffer1);
  delay(3000);
  
  randSeed(analogRead(A1));
  randNumber2 = random (0, 7);
  strcpy_P(buffer2, (char*)pgm_read_word(&(answer_table[randNumber2])));
  speakjet.print(buffer2);
  delay(3000);
  
  }
}
