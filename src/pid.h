#include "GyverTimer.h"
GTimer isTimer(MS);  
GTimer debugTimer(MS);  // Таймер для відправки відладки
bool debugEnabled = false; // Прапорець для включення/відключення відладки

float T_boyler, T_koll, T_bat, T_out;
bool hand_up, hand_down;
// bool nasos_on;
bool table_0_1_D[5];
float T_OUT;
float T_X1;
float T_Y1;
float T_X2;
float T_Y2;
float T_SET;
bool ON_OFF;
bool AUTO_HAND;
bool HAND_UP;
bool HAND_DOWN;
float SET_VALUE;
float PRESENT_VALUE;
bool PULSE_100MS;
float CYCLE;
float VALVE;
float K_P;
float K_I;
float K_D;
float DEAD_ZONE;
bool UP;
bool DOWN;
bool nasos_valve;
float TIMER_PID; // Внутренний таймер ПИД
float E_1; // Текущее рассогласование
float E_2; // Рассогласование на -1 шаг
float E_3; // Рассогласование на -2 шага
float D_T; // Время воздействия на текущем шагу регулирования
float SUM_D_T; // Накопленное время воздействия
float TIMER_PID_UP; // Накопленное время открытия
float TIMER_PID_DOWN; // Накопленное время закрытия
boolean PID_PULSE; // Шаг выполнения 1 цикла
bool _gtv1; //Импульс при старте программы
bool _gtv2; //Импульст 100 мс
bool _trgrt1 = 0;
bool _trgrt1I = 0;
bool _changeNumber5_Out = 0;
float _changeNumber5_OLV;
bool _SEEPR10OSN = 0;
bool _changeNumber4_Out = 0;
float _changeNumber4_OLV;
bool _SEEPR9OSN = 0;
bool _changeNumber3_Out = 0;
float _changeNumber3_OLV;
bool _SEEPR8OSN = 0;
bool _SEEPR1OSN = 0;
bool _gen1I = 0;
bool _gen1O = 0;
unsigned long _gen1P = 0UL;
bool _changeNumber2_Out = 0;
float _changeNumber2_OLV;
bool _SEEPR7OSN = 0;
bool _changeNumber1_Out = 0;
float _changeNumber1_OLV;
bool _SEEPR6OSN = 0;
bool _SEEPR5OSN = 0;
unsigned long _d18x2x2Tti = 0UL;
float _d18x2x2O = 0.00;
bool _SEEPR4OSN = 0;
bool _BitChange_1_OldSt = 0;
bool _BitChange_1_Out = 0;
bool _changeNumber10_Out = 0;
float _changeNumber10_OLV;
bool _changeNumber9_Out = 0;
float _changeNumber9_OLV;
bool _SEEPR3OSN = 0;
bool _SEEPR2OSN = 0;
unsigned long _d18x2x1Tti = 0UL, timer;
float _d18x2x1O = 0.00;
bool _trgrt2 = 0;
bool _trgrt2I = 0;
bool _changeNumber8_Out = 0;
float _changeNumber8_OLV;
bool _changeNumber7_Out = 0;
float _changeNumber7_OLV;
bool _changeNumber6_Out = 0;
float _changeNumber6_OLV;
bool _SEEPR11OSN = 0;
bool _tempVariable_bool;
float _tempVariable_float;

    // void turnNasosOn() {
    //     digitalWrite(nasos_otop, HIGH);
    //     eeprom.nasos_on = true;
    // }

    // void turnNasosOff() {
    //     digitalWrite(nasos_otop, LOW);
    //     eeprom.nasos_on = false;
    // }

    // void valve_UP(){
        
    //     digitalWrite(PIN_HIGH, LOW);
    //     digitalWrite(PIN_LOW, HIGH);
    // }

    // void valve_UP_STOP(){
    //     digitalWrite(PIN_HIGH, HIGH);
    // }

    // void valve_DOWN(){
    //     digitalWrite(PIN_LOW, LOW);
    //     digitalWrite(PIN_HIGH, HIGH);
    // }

    // void valve_DOWN_STOP(){

    //     digitalWrite(PIN_LOW, HIGH);
    // }
void setup_pid()
{
 
    isTimer.setInterval(50);
    debugTimer.setInterval(5000); // Встановлення інтервалу для відладки


}
void loop_pid()
{
// Основна умова
if (true) {
    if (_trgrt1I) {
        _trgrt1 = 0;
    } else {
        _trgrt1 = 1;
        _trgrt1I = 1;
    }
} else {
    _trgrt1 = 0;
    _trgrt1I = 0;
}
_gtv1 = _trgrt1;

// Умови для генератора
if (true) {
    if (!_gen1I) {
        _gen1I = 1;
        _gen1O = 1;
        _gen1P = millis();
    }
} else {
    _gen1I = 0;
    _gen1O = 0;
}

// Таймер для генератора
if (_gen1I) {
    if (millis() - timer > 50) {
        timer = millis();
        _gen1P = millis();
        _gen1O = !_gen1O;
    }
}

// Перемикання тригерів
if (_gen1O) {
    if (_trgrt2I) {
        _trgrt2 = 0;
    } else {
        _trgrt2 = 1;
        _trgrt2I = 1;
    }
} else {
    _trgrt2 = 0;
    _trgrt2I = 0;
}
_gtv2 = _trgrt2;

// Розрахунок цільової температури
T_OUT = T_out;
T_X1 = eeprom.temp_min_out;
T_Y1 = eeprom.temp_max_heat;
T_X2 = eeprom.temp_max_out;
T_Y2 = eeprom.temp_off_otop;

if (T_OUT <= T_X1) {
    T_SET = T_Y1;
} else if (T_OUT > T_X1 && T_OUT < T_X2) {
    if (T_X1 == T_X2) {
        T_X1 += 0.1;
    }
    T_SET = (T_OUT - T_X1) * (T_Y1 - T_Y2) / (T_X1 - T_X2) + T_Y1;
} else {
    T_SET = T_Y2;
}
_tempVariable_float = eeprom.temp_u_b;

// Параметри для ПІД-регулювання
ON_OFF = eeprom.heat_otop;
AUTO_HAND = eeprom.valve_mode;
HAND_UP = hand_up;
HAND_DOWN = hand_down;
SET_VALUE = _tempVariable_float;
PRESENT_VALUE = T_bat;
PULSE_100MS = _gtv2;
CYCLE = eeprom.per_on;
VALVE = eeprom.per_off;
K_P = eeprom.kof_p;
K_I = eeprom.kof_i;
K_D = eeprom.kof_d;
DEAD_ZONE = eeprom.dead_zone;

// Розрахунок розбіжності
E_1 = SET_VALUE - PRESENT_VALUE;

// Перевірка поділу на нуль та обмеження
K_I = (K_I == 0.0) ? 9999.0 : K_I;
CYCLE = (CYCLE == 0.0) ? 1.0 : CYCLE;
K_P = constrain(K_P, -99.0, 99.0);
K_I = constrain(K_I, 1.0, 9999.0);
K_D = constrain(K_D, 0.0, 9999.0);
CYCLE = constrain(CYCLE, 1.0, 25.0);
VALVE = constrain(VALVE, 15.0, 250.0);
 // Відправка відладочної інформації раз на 5 секунд
 if (debugEnabled && debugTimer.isReady()) {
    Serial.println("=== Debug Info ===");
    Serial.print("T_SET: "); Serial.println(T_SET);
    Serial.print("T_OUT: "); Serial.println(T_OUT);
    Serial.print("SET_VALUE: "); Serial.println(SET_VALUE);
    Serial.print("PRESENT_VALUE: "); Serial.println(PRESENT_VALUE);
    Serial.print("E_1 (Розрахунок розбіжності): "); Serial.println(E_1);
    Serial.print("K_P: "); Serial.println(K_P);
    Serial.print("K_I: "); Serial.println(K_I);
    Serial.print("K_D: "); Serial.println(K_D);
    Serial.print("DEAD_ZONE: "); Serial.println(DEAD_ZONE);
    Serial.print("SUM_D_T: "); Serial.println(SUM_D_T);
    Serial.print("TIMER_PID_UP: "); Serial.println(TIMER_PID_UP);
    Serial.print("TIMER_PID_DOWN: "); Serial.println(TIMER_PID_DOWN);
    Serial.print("UP: "); Serial.println(UP);
    Serial.print("DOWN: "); Serial.println(DOWN);
    Serial.println("==================");
}
// Розрахунок впливу ПІД
if (PULSE_100MS && TIMER_PID == 0.0 && !PID_PULSE) {
    PID_PULSE = 1;
    D_T = K_P * (E_1 - E_2 + CYCLE * E_2 / K_I + K_D * (E_1 - 2 * E_2 + E_3) / CYCLE) * VALVE / 100.0;
    E_3 = E_2;
    E_2 = E_1;
    SUM_D_T = constrain(SUM_D_T + D_T, -VALVE, VALVE);
    if (SUM_D_T >= 0.5) {
        TIMER_PID_DOWN = 0.0;
    }
    if (SUM_D_T <= -0.5) {
        TIMER_PID_UP = 0.0;
    }
    if (E_1 < DEAD_ZONE && E_1 > -DEAD_ZONE) {
        D_T = 0.0;
        SUM_D_T = 0.0;
    }
}

if (PULSE_100MS) {
    TIMER_PID += 0.1;
}

if (ON_OFF && AUTO_HAND) {
    if (TIMER_PID >= CYCLE) {
        PID_PULSE = 0;
        TIMER_PID = 0.0;
        if (SUM_D_T >= 0.5 || SUM_D_T <= -0.5) {
            SUM_D_T = 0.0;
        }
    }
} else {
    PID_PULSE = 0;
    D_T = 0.0;
    SUM_D_T = 0.0;
    TIMER_PID = 0.0;
    E_3 = E_1;
    E_2 = E_1;
    TIMER_PID_UP = 0.0;
    TIMER_PID_DOWN = 0.0;
}

// Управління
UP = ((((SUM_D_T >= TIMER_PID && SUM_D_T >= 0.5) || D_T >= CYCLE - 0.5 || TIMER_PID_UP >= VALVE) && AUTO_HAND) || (HAND_UP && !AUTO_HAND)) && ON_OFF && !DOWN;
if (PULSE_100MS && UP) {
    TIMER_PID_UP += 0.1;
    TIMER_PID_UP = (TIMER_PID_UP > VALVE) ? VALVE : TIMER_PID_UP;
    // valve_UP();
    relayController.setRelayHigh(true); // Включаем реле


} else {
    // valve_UP_STOP();
    relayController.setRelayHigh(false); // Выключаем реле
}

DOWN = ((((SUM_D_T <= -TIMER_PID && SUM_D_T <= -0.5) || D_T <= -CYCLE + 0.5 || TIMER_PID_DOWN >= VALVE) && AUTO_HAND) || (HAND_DOWN && !AUTO_HAND)) && ON_OFF && !UP;
if (PULSE_100MS && DOWN) {
    TIMER_PID_DOWN += 0.1;
    TIMER_PID_DOWN = (TIMER_PID_DOWN > VALVE) ? VALVE : TIMER_PID_DOWN;
    // valve_DOWN();
    relayController.setRelayLow(true); // Включаем реле

}
else {
    // valve_DOWN_STOP();
    relayController.setRelayLow(false); // Выключаем реле
}


#ifdef PID
// digitalWrite(PIN_LOW, !DOWN);
// digitalWrite(PIN_HIGH, !UP);

// Керування нагрівом
if (eeprom.heat_state) {
    eeprom.heat_otop = true;
    relayController.setLed(true); // Включаем светодиод
} else {
    eeprom.heat_otop = false;
    relayController.setLed(false); // Выключаем светодиод
}

// Вимкнення нагріву при досягненні потрібної температури
if (eeprom.heat_otop){
   
    nasos_valve = HIGH;}
    
else {nasos_valve = LOW;}
// Управління насосом
if (nasos_valve) {
    relayController.setRelayNasos(true); // Включаем насос
    eeprom.nasos_on = true;
} else {
    relayController.setRelayNasos(false); // Выключаем насос
    eeprom.nasos_on = false;
}
#endif


}

// Функція для включення/відключення відладки
void toggleDebug(bool enable) {
    debugEnabled = enable;
}