 /* 
  Code based on LCDemoMatrix Example from Arduino 
   
  Displays different emote eyes on two 8x8 LED Matrices 
  This one should work with the auto-generated mid-frame "cookie cutter" 
  
  KaiX Emotes 
  Version 2.0 //cleaned up from V1 
  Authors: Geeling Chau and Austin Hermida
 */ 
 
 
#include "LedControl.h" 
 
 
/* 
 pin 12 is connected to the DataIn  
 pin 11 is connected to the CLK  
 pin 10 is connected to LOAD  
 We have two eyes  
 */ 
LedControl lc=LedControl(12,11,10,2); 
 
 
/* we always wait a bit between updates of the display */ 
unsigned long delayTime=1000; 
const int MATRIX_SIZE = 8; //8x8 matrix 
 
 
byte openEye[MATRIX_SIZE] =  
{0, 60, 102, 102, 126, 126, 60, 0};  
/*{0b00000000, 
0b00111100, 
0b01100110, 
0b01100110, 
0b01111110, 
0b01111110, 
0b00111100, 
0b00000000};*/ //{0x00,0x3c,0x66,0x66,0x7e,0x7e,0x3c,0x00}; 
byte closedEye[MATRIX_SIZE] =  
{0, 8, 8, 8, 8, 8, 8, 0}; 
/*{0b00000000, 
0b00001000, 
0b00001000, 
0b00001000, 
0b00001000, 
0b00001000, 
0b00001000, 
0b00000000};*/ // {0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x00};  
byte generalInBetween[MATRIX_SIZE] = 
{0, 24, 60, 60, 60, 60, 24, 0};  
/*{0b00000000, 
0b00011000, 
0b00111100, 
0b00111100, 
0b00111100, 
0b00111100, 
0b00011000, 
0b00000000};*/ //{0x00,0x18,0x3c,0x3c,0x3c,0x3c,0x18,0x00};  
byte angryEye[MATRIX_SIZE] = {0x00,0x06,0x0e,0x1e,0x3e,0x7e,0x7e,0x00};  
byte happyEye[MATRIX_SIZE] = {0x04,0x08,0x10,0x20,0x20,0x10,0x08,0x04};  
byte sadEye[MATRIX_SIZE] = {0x00,0x7e,0x7e,0x3e,0x1e,0x0e,0x06,0x00};  
 
 
 
 
unsigned long openEyeTimer = 0;  
unsigned long openEyeDelayTime = 1; // 20 milliseconds between each frame 
unsigned int openEyeFrameCounter = 0;  
 
 
unsigned long closeEyeTimer = 0;  
unsigned long closeEyeDelayTime = 1; // 20 milliseconds between each frame  
int closedEyeFrameCounter = 2; 
 
 
void setup() { 
  //wake up MAX72XX 
  lc.shutdown(0,false); 
  lc.shutdown(1,false); 
   
  //set brightness to mediumish levels 
  lc.setIntensity(0,4); 
  lc.setIntensity(1,4); 
   
  //clear display 
  lc.clearDisplay(0); 
  lc.clearDisplay(1); 
   
  //To be able to write to Serial Monitor 
  Serial.begin(9600);  
} 
 
 
void loop() { 
  displayEye(openEye);  
   
  displayEye(happyEye);  
   
   displayEye(sadEye);  
    
    displayEye(angryEye);  
   
  displayEye(closedEye);  
} 
 
 
void displayEye(byte eye[]){ 
  openTheEye(eye); 
  delay(1000);   
  closeTheEye(eye);  
  delay(100); 
} 
 
 
byte* cookieCut(byte a[]){ 
  byte resultingArray[MATRIX_SIZE] = {0,0,0,0,0,0,0,0};  
   
  for (int i = 0; i < MATRIX_SIZE; i++) { 
    resultingArray[i] = a[i] & generalInBetween[i];  
  } 
   
  return resultingArray;  
} 
 
 
 
 
void openTheEye(byte eye[]) { 
  while(openEyeFrameCounter < 3) { 
    if(millis() - openEyeTimer > openEyeDelayTime) { 
      switch(openEyeFrameCounter) { 
        case 0: displayByteArrayOnA(closedEye);  
        displayByteArrayOnB(closedEye); 
        openEyeFrameCounter++;  
        break;  
        case 1: displayByteArrayOnA(cookieCut(eye)); 
        displayByteArrayOnB(cookieCut(eye)); 
        openEyeFrameCounter++;  
        break;  
        case 2: displayByteArrayOnA(eye); 
        displayByteArrayOnB(eye); 
        openEyeFrameCounter++;  
        break;  
      } 
       
      openEyeTimer = millis();  
    } 
  } 
  openEyeFrameCounter = 0; 
} 
 
 
void closeTheEye(byte eye[]) { 
  while(closedEyeFrameCounter >= 0) { 
    if(millis() - closeEyeTimer > closeEyeDelayTime) { 
      switch(closedEyeFrameCounter) { 
        case 0: displayByteArrayOnA(closedEye);  
        displayByteArrayOnB(closedEye); 
        closedEyeFrameCounter--;  
        break;  
        case 1: displayByteArrayOnA(cookieCut(eye)); 
        displayByteArrayOnB(cookieCut(eye)); 
        closedEyeFrameCounter--;  
        break;  
        case 2: displayByteArrayOnA(eye); 
        displayByteArrayOnB(eye); 
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
