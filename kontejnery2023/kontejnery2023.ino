#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;


char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

#define ARRAY_SIZE(my_array) ((sizeof(my_array))/(sizeof(my_array[0])))

//LED colors
int blue = 6;
int white = 11;
int yellow = 9;
int green = 10;

int mainColor = 0;
int colorCollective1 = 0;
int colorCollective2 = 0;

int plastic[12][3] = {{13, -1, -1},         
                     {10, -1, -1},   
                     {10, -1, -1},  
                     {7, -1, -1},  
                     {5, -1, -1},  
                     {2, 30, -1},  
                     {28, -1, -1},
                     {25, -1, -1},
                     {22, -1, -1},
                     {20, -1, -1},
                     {17, -1, -1},
                     {15, -1, -1}}; 

int bio[12][3] = {{30, -1, -1},         
                  {27, -1, -1},   
                  {27, -1, -1},  
                  {14, 24, -1},  
                  {22, -1, -1},  
                  {19, -1, -1},  
                  {17, -1, -1},
                  {14, -1, -1},
                  {11, -1, -1},
                  {9, -1, -1},
                  {6, -1, -1},
                  {4, -1, -1}};  

int all[12][3] = {{16, -1, -1},         
                  {13, -1, -1},   
                  {-1, -1, -1},  
                  {11, -1, -1},  
                  {-1, -1, -1},  
                  {-1, -1, -1},  
                  {-1, -1, -1},
                  {-1, -1, -1},
                  {-1, -1, -1},
                  {-1, -1, -1},
                  {-1, -1, -1},
                  {18, -1, -1}};   

int paper[12][3] = {{27, -1, -1},         
                    {24, -1, -1},   
                    {24, -1, -1},  
                    {21, -1, -1},  
                    {19, -1, -1},  
                    {16, -1, -1},  
                    {14, -1, -1},
                    {11, -1, -1},
                    {8, -1, -1},
                    {6, -1, -1},
                    {3, -1, -1},
                    {1, 29, -1}};  

int collective[12][3] = {{21, -1, -1},         
                        {-1, -1, -1},   
                        {13, -1, -1},  
                        {-1, -1, -1},  
                        {8, -1, -1},  
                        {5, -1, -1},  
                        {3, 31, -1},
                        {28, -1, -1},
                        {25, -1, -1},
                        {23, -1, -1},
                        {20, -1, -1},
                        {-1, -1, -1}};

int Hour = 0;
int Month = 0;
int Day = 0;


/////////////-LEDS-//////////////////////
void stayOn(int color){
  analogWrite(color, 5);
}

void turnOff(int color){
  analogWrite(color, LOW);
}


void breath (int color)
{
  for(int a = 0; a < 15; a++)
  {
    analogWrite(color, a);
     if(a<20)
     {
      delay(50);
     }
     else
     {
      delay(10);
     }
  }
  delay(800);

  for(int a = 15; a >= 0; a--)
  {
    analogWrite(color, a);
     if(a<20)
     {
      delay(50);
     }
     else
     {
      delay(10);
     }
  }
  delay(800);
}

void collectiveBreath (int color1, int color2)
{
  for(int a = 0; a < 15; a++)
  {
    analogWrite(color1, a);
    analogWrite(color2, a);
     if(a<20)
     {
      delay(50);
     }
     else
     {
      delay(10);
     }
  }
  delay(400);

  for(int a = 15; a >= 0; a--)
  {
    analogWrite(color1, a);
    analogWrite(color2, a);
     if(a<20)
     {
      delay(50);
     }
     else
     {
      delay(10);
     }
  }
  delay(400);
}
/////////////-LEDS=ENDs-////////////////////////////////////////////////////



void setup() {
  // put your setup code here, to run once:

  pinMode(white, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

  Serial.begin(9600);
  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC lost power, lets set the time!");
  
  // Comment out below lines once you set the date & time.
    // Following line sets the RTC to the date & time this sketch was compiled
    
//    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));   ////************************************/////
  
    // Following line sets the RTC with an explicit date & time
    // for example to set January 27 2017 at 12:56 you would call:
    // rtc.adjust(DateTime(2017, 1, 27, 12, 56, 0));
  }
}

void loop() {
  // put your main code here, to run repeatedly:

    DateTime now = rtc.now();
    
    Serial.println("Current Date & Time: ");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    //delay(1000);

    Hour = now.hour();
    Day = now.day();
    Month = now.month();

    Serial.println(Hour);
    Serial.println(Day);
    Serial.println(Month);

    ////////-CHECKINGforDate-////////////////////

    if((checkForDateInAdvance(plastic, yellow) || 
    checkForDateInAdvance(all, white) ||
    checkForDateInAdvance(paper, blue) ||
    checkForDateInAdvance(bio, green) ||
    checkForDateCollectiveInAdvance(collective, white, green)) && (Hour > 6 && Hour < 19)) 
    {
      breath(mainColor);
      collectiveBreath(colorCollective1, colorCollective2);
    }
    else if((checkForDate(plastic, yellow) || 
            checkForDate(all, white) ||
            checkForDate(paper, blue) ||
            checkForDate(bio, green) ||
            checkForDateCollective(collective, white, green)) && (Hour > 6 && Hour < 19))
    {
      stayOn(mainColor);
      stayOn(colorCollective1);
      stayOn(colorCollective2);
    }
    else{
      Serial.println("fail");
      turnOff(mainColor);
      turnOff(colorCollective1);
      turnOff(colorCollective2);
    }
    
    ////////-CHECKINGforDate=ENDs-//////////////

}


/////////////-DATEcheck-////////////////////////////////////////////////////
bool checkForDate(int my_array[12][3], int color){
  for(int i = 0; i<12; i++){
    for(int j = 0; j<3; j++){
      if(Month == i+1 && Day == my_array[i][j]){
        mainColor = color;
        Serial.print("Curr day");
        Serial.print("Day");
        Serial.println(Day);
        Serial.print("Month");
        Serial.println(Month);
        Serial.print("Hour");
        Serial.println(Hour);
        return true;
        break;
      }
    }
  }
  return false;
}

//1_day in advance

bool checkForDateInAdvance(int my_array[12][3], int color){
  for(int i = 0; i<12; i++){
    for(int j = 0; j<3; j++){
      if(Month == i+1 && Day == my_array[i][j]-1){
        mainColor = color;
        Serial.println("In advance");
        Serial.print("Day");
        Serial.println(Day);
        Serial.print("Month");
        Serial.println(Month);
        Serial.print("Hour");
        Serial.println(Hour);
        return true;
        break;
      }
    }
  }
  return false;
}
/////////////-DATEcheck=ENDs-//////////////////////

///---------------------------------------------------------///

////////////-DATEcheckFORCollective-//////////////

bool checkForDateCollective(int my_array[12][3], int color1, int color2){
  for(int i = 0; i<12; i++){
    for(int j = 0; j<3; j++){
      if(Month == i+1 && Day == my_array[i][j]){
        colorCollective1 = color1;
        colorCollective2 = color2;
        Serial.print("Curr day");
        Serial.print("Day");
        Serial.println(Day);
        Serial.print("Month");
        Serial.println(Month);
        Serial.print("Hour");
        Serial.println(Hour);
        return true;
        break;
      }
    }
  }
  return false;
}

//1_day in advance

bool checkForDateCollectiveInAdvance(int my_array[12][3], int color1, int color2){
  for(int i = 0; i<12; i++){
    for(int j = 0; j<3; j++){
      if(Month == i+1 && Day == my_array[i][j]-1){
        colorCollective1 = color1;
        colorCollective2 = color2;
        Serial.println("In advance");
        Serial.print("Day");
        Serial.println(Day);
        Serial.print("Month");
        Serial.println(Month);
        Serial.print("Hour");
        Serial.println(Hour);
        return true;
        break;
      }
    }
  }
  return false;
}
////////////-DATEcheckFORCollective=ENDs-//////////////
