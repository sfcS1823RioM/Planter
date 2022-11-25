#ifndef PlantProject_h
#define PlantProject_h

#include "Arduino.h"

class PlantProject
{
public:
    PlantProject(int number1, int number2);
    void initialize(void);
    void setDebugMode(boolean flag);
    void setLimitHumidity(int humidity);
    void setLimitTime(int hour1, int hour2, int minute, int second);
    // check
    void checkHumidity(void);
    void checkFlag(int hour, int minute, int second);
    // active
    void activePomp(void);

private:
    // PinMode
    int soilSensorPinNum;
    int pompPinNum;
    // Time
    int limitHour1, limitHour2, limitMinute, limitSecond;
    // Soil
    int limitHumidity;
    int value;
    // others
    boolean debugFlag;
    boolean limitFlag;
};
#endif
