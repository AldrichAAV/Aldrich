#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
//comentario de prueba para ver si se cambia
class conexionWeb{
  private:
  public:
    conexionWeb(const char *_SSID, const char* _PASSWORD ){
      WiFi.begin(_SSID, _PASSWORD);
      while(WiFi.status()!= WL_CONNECTED){
          delay(500);
          Serial.print("...");
      }
    }
}; 

class Tiempo
{
private:
  int defaultTime;
  struct tm timeinfo;
  const char *ntpServer = "pool.ntp.org";
  const long gmtOffset_sec = 0;
  const int daylightOffset_sec = 0;
public:
  char timeStringBuff[20];
  Tiempo()
  {
    defaultTime = 0;
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    getTime();
  }
  void getTime()
  {   
    setLocalTime();
  }
  void setLocalTime()
  {
    if (!getLocalTime(&timeinfo))
    {
    }
    strftime(timeStringBuff, sizeof(timeStringBuff), "%Y-%m-%dT%H:%M:%SZ", &timeinfo);
  }
};
conexionWeb *webInterface;
Tiempo *reloj;
StaticJsonDocument<512> horaActual;
const char *ssid="CGA2121_W3dpsKv";
const char *passwrd="fvwMetJLPR4XP8aekEP";
void setup() {
  Serial.begin(115200);
  webInterface= new conexionWeb(ssid,passwrd);
  reloj=new Tiempo();
}
int suma=0;
void loop() {
  suma++;
  horaActual.clear();
  reloj->getTime();
  horaActual["hora"]=reloj->timeStringBuff;
  horaActual["Sumatoria"]=suma;
  serializeJson(horaActual,Serial);
  Serial.println("");
  delay(1000);
}

