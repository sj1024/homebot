// ESP8266_Blynk_Aircon (2016.8.13)
 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
 
char auth[] = "";   // your Blynk Auth Token
const char* ssid = "";                         // your ssid
const char* password = "";                // your password
 
int onSignal[]  = {3100,-9800,470,-1550,470,-550,470,-550,470,-550,470,-1550,470,-550,470,-550,470,-550,470,-550,470,-550,470,-550,470,-550,470,-550,470,-550,470,-550,470,-550,470,-1550,470,-1550,470,-550,470,-550,470,-550,470,-1550,470,-550,470,-550,470,-550,470,-550,470,-550,470,-550,470,0};
int offSignal[] = {3100,-9800,470,-1550,470,-550,470,-550,470,-550,470,-1550,470,-550,470,-550,470,-550,470,-1550,470,-1550,470,-550,470,-550,470,-550,470,-550,470,-550,470,-550,470,-550,470,-550,470,-550,470,-550,470,-550,470,-1550,470,-550,470,-1550,470,-550,470,-550,470,-550,470,-1550,470,0};
int testSignal[] = {9000,-4500,500,-500,500,-500,500,-1500,500,-500,500,-500,500,-500,500,-500,500,-500,500,-1500,500,-1500,500,-500,500,-1500,500,-1500,500,-1500,500,-1500,500,-1500,500,-500,500,-500,500,-1500,500,-500,500,-500,500,-500,500,-1500,500,-500,500,-1500,500,-1500,500,-500,500,-1500,500,-1500,500,-1500,500,-500,500,-1500,500,0};
 
int pinBlynk = 2;                                   // onboard LED pin of ESP-12F
int pinRemote = 5;                                  // GPIO pin 5 (D1 of NodeMCU, WeMos D1 Mini)
int airconStatus;
 
void setup()
{
  Blynk.begin(auth, ssid, password);

  pinMode(pinRemote,OUTPUT);
  airconStatus = digitalRead(pinBlynk);
}
 
void loop()
{
  Blynk.run();
 
  if(airconStatus == !digitalRead(pinBlynk)) {
    if(digitalRead(pinBlynk)==LOW) {
      IRsend(pinRemote,onSignal);     
    }
    else {
      IRsend(pinRemote,offSignal);
    }
    airconStatus = digitalRead(pinBlynk);
  }
}
 
void IRsend(int IRpin, int IRsignal[]) {
  int i=0;
  pinMode(IRpin, OUTPUT);
  do {
    if (IRsignal[i]>0) {
      int duration = IRsignal[i];
      while (duration > 0) {
        digitalWrite(IRpin, HIGH);
        delayMicroseconds(10);
        digitalWrite(IRpin, LOW);
        delayMicroseconds(10);
        duration -= 26;         // 38 kHz = 26.3 uSec
      }
    }
    else {
      delayMicroseconds(abs(IRsignal[i]));
    }
    i+=1;
  }
  while (IRsignal[i] != 0);
}

