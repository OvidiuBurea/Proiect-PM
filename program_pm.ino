const int PIN_RED   = 6; //Red LED on pin 9
const int PIN_GREEN = 7; //Green LED on pin 10
const int PIN_BLUE  = 5; //Blue LED on Pin 11
const int buttonPin1 = 3;
const int buttonPin2 = 4;

#include "SD.h"
#define SD_ChipSelectPin 10
#include "TMRpcm.h"
#include "SPI.h"

TMRpcm music;
#define sensorPin A0
  
//variables to hold our color intensities
int red;
int green;
int blue;
int buttonState = 0;
int buttonMusic = 0;
int song_number=0;
int soilmoist = 0;
int light = 0;
  
/* This function "Set Color" will set the color of the LED
   rather than doing it over and over in the loop. */
void setColor(int R, int G, int B) {
  analogWrite(PIN_RED,   R);
  analogWrite(PIN_GREEN, G);
  analogWrite(PIN_BLUE,  B);
}

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(PIN_RED,   OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE,  OUTPUT);

  if(!SD.begin(SD_ChipSelectPin))
  {
  Serial.println("SD fail");
  return;
  }
  music.speakerPin = 9;
  music.setVolume(5);
  music.quality(1);
}

void loop() {
  buttonState = digitalRead(buttonPin2);
  buttonMusic = digitalRead(buttonPin1);
  //setColor(255, 0, 0); //set LED to Red
  //delay(500);
  //setColor(0, 255, 0); //set LED to Green
  //delay(500);
  //setColor(0, 0, 255); //set LED to Blue
  //delay(500);
  // no need to repeat the melody.

  Serial.print("Analog output: ");
  soilmoist = readSensor();
  Serial.println(soilmoist);

  light = analogRead(A1);
  Serial.print("Analog lumina: ");
  Serial.println(light);

  if (soilmoist < 5 && light < 200) {
    setColor(255, 0, 0);
    red = 1;
    green = 0;
    blue = 0;
  }
  else {
    if (soilmoist < 5) {
      setColor(0, 0, 255);
      blue = 1;
      green = 0;
      red = 0;
    }
    else {
      setColor(0, 255, 0);
      green = 1;
      blue = 0;
      red = 0;
    }
  }

  if(buttonState == LOW) {
    if (green == 1) {
      music.play("g.wav");
    }
    if (blue == 1) {
      music.play("w.wav");
    }
    if (red == 1) {
      music.play("s.wav");
    }
    green = 0;
    blue = 0;
    red = 0;
  }

  if(buttonMusic == LOW) {
    song_number++;
    if (song_number==9)
    {song_number=1;}
    if (song_number ==1)
    {music.play("1.wav");}
    if (song_number == 2)
    {music.play("2.wav");}
    if (song_number ==3)
    {music.play("3.wav");}
    if (song_number ==4)
    {music.play("4.wav");}
    if (song_number ==5)
    {music.play("5.wav");}
    if (song_number ==6)
    {music.play("6.wav");}
    if (song_number ==7)
    {music.play("7.wav");}
    if (song_number ==8)
    {music.play("8.wav");}
  }
}

int readSensor() {
  int sensorValue = analogRead(sensorPin);
  int outputValue = map(sensorValue, 0, 1023, 255, 0);
  return outputValue;
}
