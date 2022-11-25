#include "PlantProject.h"

PlantProject::PlantProject(int number1, int number2)
{
  // PinMode
  soilSensorPinNum = number1;
  pompPinNum = number2;
}

void PlantProject::initialize(void)
{
  // pinMode
  pinMode(soilSensorPinNum, INPUT);
  pinMode(pompPinNum, OUTPUT);
  // Time
  limitHour1 = 0;
  limitHour2 = 0;
  limitMinute = 0;
  limitSecond = 0;
  // Soil
  limitHumidity = 0;
  value = -1;
  checkHumidity();
  setLimitHumidity(value);
  // others
  limitFlag = false;
}

void PlantProject::setDebugMode(boolean flag)
{
  debugFlag = flag;
}

void PlantProject::setLimitHumidity(int humidity)
{
  limitHumidity = humidity;
}

void PlantProject::setLimitTime(int hour1, int hour2, int minute, int second)
{
  limitHour1 = hour1;
  limitHour2 = hour2;
  limitMinute = minute;
  limitSecond = second;
}

void PlantProject::checkHumidity(void)
{
  // read_ValueOfSensor
  value = analogRead(soilSensorPinNum);
  Serial.print("value: ");
  Serial.println(value);
}

void PlantProject::checkFlag(int hour, int minute, int second)
{
  // start_feed
  if (debugFlag){
    limitFlag = true;
  }
  else{
    if(hour == limitHour1 || hour == limitHour2){
      if(minute == limitMinute && second == limitSecond) limitFlag = true;
    }
  }
  // end_feed
  if(limitFlag == true){
    if(value <= limitHumidity){
      Serial.println("WET!!");
      limitFlag = false;
    }
  }
}

void PlantProject::activePomp(void)
{
  if(limitFlag){
    digitalWrite(pompPinNum, HIGH);
    Serial.println(pompPinNum);
    Serial.print("Limit: ");
    Serial.println(limitHumidity);
  }
  else digitalWrite(pompPinNum, LOW);
  Serial.print("flag: ");
  Serial.println(limitFlag);
}
