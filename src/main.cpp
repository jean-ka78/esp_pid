#include <ArduinoOTA.h>
#include <EEPROM.h>
#include "config.h"
#define PID
#include "st_enum.h"
#include "out.h"
#include "link.h"
#include "in.h"

#include "pid.h"
#include "mqtt.h"

unsigned long timer1, timer2, timer3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Initialize serial communication
  setup_out();
  setup_in();
  setupMqtt();
  setup_pid();
  toggleDebug(false);
  first_start();
  ConnectWIFI();

  ArduinoOTA.setHostname("pid_ventil"); // Задаем имя сетевого порта
  ArduinoOTA.begin(); 

  
}

void loop() {
  ArduinoOTA.handle(); // Всегда готовы к прошивке
  rssi =  map(WiFi.RSSI(), -115, -35, 0, 100);
  // loop_out();
  loop_pid();
  loopMQtt(); 
  // put your main code here, to run repeatedly:
  if (millis() - timer1>1000)
  {
    timer1 = millis();
    T_bat = get_temp();   
    SendData();
    getValues(); 

   }

  
  if (millis() - timer2>1000)
  {
    timer2 = millis();
    reconnect();
    Safe_eeprom();
  }

}
