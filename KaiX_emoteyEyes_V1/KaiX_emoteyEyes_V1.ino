/*
Code based on LCDemoMatrix Example from Arduino

Displays different emote eyes on two 8x8 LED Matrices
*/

//We always have to include the library
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,11,10,2);

/* we always wait a bit between updates of the display */
unsigned long delayTime=1000;
const int MATRIX_SIZE = 8; //8x8 matrix
const int NUM_EYES = 6; 
const int OPEN_EYE = 1; 
const int HAPPY_EYE = 2; 
const int ANGRY_EYE = 3; 
const int SAD_EYE = 4; 
const int LOW_BATTERY = 5; 
byte openEyeFrame1[MATRIX_SIZE] = {0x00,0x08,0x14,0x14,0x1c,0x1c,0x08,0x00};
byte openEyeFrame2[MATRIX_SIZE] = //{0xff,0xe7,0xdb,0xdb,0xc3,0xc3,0xe7,0xff};//
{0x00,0x18,0x24,0x24,0x3c,0x3c,0x18,0x00};
byte openEye[MATRIX_SIZE] = //{0xff,0xc3,0x99,0x99,0x81,0x81,0xc3,0xff};
{0x00,0x3c,0x66,0x66,0x7e,0x7e,0x3c,0x00}; 

byte closedEye[MATRIX_SIZE] = //{0xff,0xf7,0xf7,0xf7,0xf7,0xf7,0xf7,0xff}; 
{0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x00}; 
byte angryEye[MATRIX_SIZE] = {0x00,0x06,0x0e,0x1e,0x3e,0x7e,0x7e,0x00}; 
byte happyEye[MATRIX_SIZE] = {0x04,0x08,0x10,0x20,0x20,0x10,0x08,0x04}; 
byte sadEye[MATRIX_SIZE] = {0x00,0x7e,0x7e,0x3e,0x1e,0x0e,0x06,0x00}; 
byte batteryLowB[MATRIX_SIZE] = {0x00,0x0e,0x0a,0x0e,0x00,0x02,0x02,0x7e}; 
byte batteryLowA[MATRIX_SIZE] = {0x7e,0x5e,0x4e,0x46,0x42,0x42,0x66,0x18}; 
unsigned long timer = 0; 

unsigned long openEyeTimer = 0; 
unsigned long openEyeDelayTime = 1; // 20 milliseconds between each frame
unsigned int openEyeFrameCounter = 0; 

unsigned long closeEyeTimer = 0; 
unsigned long closeEyeDelayTime = 1; // 20 milliseconds between each frame 
int closedEyeFrameCounter = 2; 

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  lc.shutdown(1,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,4);
  lc.setIntensity(1,4);
  /* and clear the display */
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  
  Serial.begin(9600); //To be able to write to Serial Monitor
}

void loop() {
  displayByteArrayOnA(closedEye); 
  displayByteArrayOnB(closedEye); 
  delay(200); 
  openTheEye();
  delay(1000);  
  closeTheEye(); 
  delay(10);
  
  /*
  if(millis() - timer > delayTime) {
    int randNumber = random(NUM_EYES); 
    displayByteArrayOnA(closedEye); 
    displayByteArrayOnB(closedEye); 
    delay(500); 
    switch (randNumber) {
      case OPEN_EYE: //displayOpenEye(); 
      displayByteArrayOnA(openEye);
      displayByteArrayOnB(openEye); 
      delayTime = 1000; 
      break; 
      case HAPPY_EYE: displayByteArrayOnA(happyEye); 
      displayByteArrayOnB(happyEye); 
      delayTime = 1000; 
      break; 
      case ANGRY_EYE: displayByteArrayOnA(angryEye); 
      displayByteArrayOnB(angryEye); 
      delayTime = 1000; 
      break; 
      case SAD_EYE: displayByteArrayOnA(sadEye); 
      displayByteArrayOnB(sadEye); 
      delayTime = 1000; 
      break;
      case LOW_BATTERY: displayByteArrayOnA(batteryLowA); 
      displayByteArrayOnB(batteryLowB); 
      delayTime = 1000; 
      break; 
      default: displayByteArrayOnA(closedEye); 
      displayByteArrayOnB(closedEye); 
      delayTime = 10; 
      break; 
    }
    timer = millis(); 
  }*/
  
}

void openTheEye() {
  while(openEyeFrameCounter < 3) {
    if(millis() - openEyeTimer > openEyeDelayTime) {
      switch(openEyeFrameCounter) {
        case 0: displayByteArrayOnA(closedEye); 
        displayByteArrayOnB(closedEye);
        openEyeFrameCounter++; 
        break; 
        case 1: displayByteArrayOnA(openEyeFrame2);
        displayByteArrayOnB(openEyeFrame2);
        openEyeFrameCounter++; 
        break; 
        case 2: displayByteArrayOnA(openEye);
        displayByteArrayOnB(openEye);
        openEyeFrameCounter++; 
        break; 
      }
      
      openEyeTimer = millis(); 
    }
  }
  openEyeFrameCounter = 0;
}

void closeTheEye() {
  while(closedEyeFrameCounter >= 0) {
    if(millis() - closeEyeTimer > closeEyeDelayTime) {
      switch(closedEyeFrameCounter) {
        case 0: displayByteArrayOnA(closedEye); 
        displayByteArrayOnB(closedEye);
        closedEyeFrameCounter--; 
        break; 
        case 1: /*displayByteArrayOnA(openEyeFrame1);
        displayByteArrayOnB(openEyeFrame1);
        closedEyeFrameCounter--; 
        break; 
        case 2:*/ displayByteArrayOnA(openEyeFrame2);
        displayByteArrayOnB(openEyeFrame2);
        closedEyeFrameCounter--; 
        break; 
        case 2: displayByteArrayOnA(openEye);
        displayByteArrayOnB(openEye);
        closedEyeFrameCounter--; 
        break; 
      }
      Serial.println(closedEyeFrameCounter); 
      closeEyeTimer = millis(); 
    }
  }
  closedEyeFrameCounter = 2;
}


void displayByteArrayOnA(byte a[]) {
  for(int i=0; i<MATRIX_SIZE; i++) {
    lc.setColumn(0,i,a[i]);
  }
}

void displayByteArrayOnB(byte a[]) {
  for(int i=MATRIX_SIZE-1; i>=0; i--) {
    lc.setColumn(1,MATRIX_SIZE - i - 1,a[i]);
  }
}
