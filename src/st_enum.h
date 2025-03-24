#include <EEPROM.h>

struct st_Enum
{
  float temp_u;     // Уставка бойлера
  float temp_u_b;   // Уставка батарей
  float temp_off_otop; // Уставка отключения отопления
  float gis_boy;  // Гистерезис бойлер
  float temp_min_out;
  float temp_max_out;
  float temp_max_heat;
  float dead_zone;
  float kof_p;
  float kof_i;
  float kof_d;
  bool init;
  bool heat; // Флаг включения бойлера
  bool boy_state;
  bool heat_otop; // Флаг включения отопления
  bool heat_state;
  bool summer; 
  bool valve_mode;
  bool nasos_on;
  int per_on; // Период включения 
  int per_off; // Период выключения
  int time_valve;
} eeprom;

#define INIT_ADDR 1  // Номер резервной ячейки
#define INIT_KEY 1   // Ключ первого запуска. 0-254, на выбор

void first_start()
{
  EEPROM.begin(sizeof(st_Enum));
  EEPROM.get(0, eeprom);
  // Serial.println("first start read address: " + String(eeprom.init));
  if (eeprom.init != INIT_KEY) { // Первый запуск
    eeprom.init = INIT_KEY;    // Записали ключ

    // EEPROM.get(0, eeprom);
    // --------------------------------------
    // Заводские настройки 
    eeprom.temp_u = 60;
    eeprom.temp_u_b = 18.5;
    eeprom.temp_off_otop = 30;
    eeprom.gis_boy = -1.5;
    eeprom.heat = true;
    eeprom.boy_state = true;
    eeprom.heat_otop = true;
    eeprom.heat_state = true;
    eeprom.valve_mode = true;
    eeprom.per_on = 10;
    eeprom.per_off = 120;
    eeprom.kof_p = 3;
    eeprom.kof_i = 30;
    eeprom.kof_d = 10;
    eeprom.temp_max_out = 15;
    eeprom.temp_min_out = -15;
    eeprom.temp_max_heat = 60;
    eeprom.dead_zone = 1;

    EEPROM.begin(sizeof(st_Enum));
    EEPROM.put(0, eeprom);
    delay(50);
    EEPROM.commit();
  }
}

void Safe_eeprom()
{
  EEPROM.begin(sizeof(st_Enum));
  EEPROM.put(0, eeprom);
  delay(10);
  EEPROM.commit();
}