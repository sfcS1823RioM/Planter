#include <WiFi.h>
#include "time.h"
#include "PlantProject.h"

// PIN
const int soilSensor[2] = {36, 39};
const int pomp[2] = {5, 17};
// humidity
const int humidity[2] = {1500, 1650};
// Time
const int JST = 3600*9;
int hour[2] = {8, 17};
const int minute = 0;
const int second = 0;
// Wifi
const char *ssid = "*****";
const char *password = "*****"; 
// Time
int _time[3];
time_t t;
struct tm *tm;

PlantProject project[2] = {
  PlantProject(soilSensor[0], pomp[0]),
  PlantProject(soilSensor[1], pomp[1])
};
const int numberOfProject = sizeof(project)/sizeof(PlantProject);

void setup(){
  // Serial
  Serial.begin(115200);
  Serial.println("HelloWorld!");
  setWifi();
  for(int i=0; i < numberOfProject; i++){
    project[i].initialize();
    // setup
    project[i].setDebugMode(false);
    project[i].setLimitTime(hour[0], hour[1], minute, second);
    Serial.println(i+": setup");
  }
  pinMode(2, OUTPUT);
}

void loop(){
  setTime();
  for(int i=0; i < numberOfProject; i++){
    project[i].checkHumidity();
    project[i].checkFlag(tm->tm_hour, tm->tm_min, tm->tm_sec);
    project[i].activePomp();
  }
  if(tm->tm_hour >= 8 && tm->tm_hour < 17){
    digitalWrite(2, LOW);
  }else{
    digitalWrite(2, HIGH);
  }
  delay(1000);
}

void setWifi(){
  // WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(500);
  }
  Serial.println();
  Serial.printf("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  // Time
  configTime(JST, 0, "ntp.nict.jp", "ntp.jst.mfeed.ad.jp");
}

void setTime(){
  t = time(NULL);
  tm = localtime(&t);
  Serial.printf(" %04d/%02d/%02d %02d:%02d:%02d\n",
        tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
        tm->tm_hour, tm->tm_min, tm->tm_sec);
//  _time = {tm->tm_hour, tm->tm_min, tm->tm_sec};
}
