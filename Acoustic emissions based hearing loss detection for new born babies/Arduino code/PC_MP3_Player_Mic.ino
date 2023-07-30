#include <LiquidCrystal.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(2,3); // RX, TX

LiquidCrystal lcd{8, 9, 10, 11, 12, 13};

int swi=4;

DFRobotDFPlayerMini myDFPlayer;

long int so1,so2;
int flag=0;
char str[10];

void printDetail(uint8_t type, int value);

void waitMilliseconds(uint16_t msWait) {
  uint32_t start = millis();

  while ((millis() - start) < msWait) {
        delay(1);
  }
}




void setup() {

  Serial.begin(9600);
  Serial.println("Device Started");

   mySoftwareSerial.begin(9600);

   pinMode(A3,INPUT);
   pinMode(A2,OUTPUT);

   digitalWrite(A2,LOW);

  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print(" Sound Measuring ");
  lcd.setCursor(0,1);
  lcd.print("     System      ");
  delay(1000);
  
 
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30  
  
 
  
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Awaiting Command");

   
}

void loop() {
  static long pms = 0;

    if(digitalRead(A3)==0)
    {
     myDFPlayer.play(1);  //Play the first mp3 
     delay(1000);
     flag=1;
    }
 
    while(flag==1)
    {
      so1=analogRead(A0);
      delay(200);
      so2=analogRead(A1);
      delay(200);
      sprintf(str,"%04ld,%04ld",so1,so2);
      Serial.println(str);
      serialEvent();
    }
   
  
  delay(300);
}

void serialEvent() {

char val;
while(Serial.available())
    {
    val=Serial.read();
    //Serial.print(val);
    switch(val)
    {
     case 'A':
     lcd.setCursor(0,1);
     lcd.print("No Hearing Loss   ");
     delay(2000);
     break;
    case 'B':
     lcd.setCursor(0,1);
     lcd.print("Hearing Issues    ");
     delay(2000);
     break;
     case 'C':
     lcd.setCursor(0,1);
     lcd.print("                  "); 
     break;
    }
      flag=0;
      
      Serial.println("Stopped");
      
    }

      
  
}


  
void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }

}
