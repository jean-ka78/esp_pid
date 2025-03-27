class ControlSystem {
  private:
    const int pinLow;
    const int pinHigh;
    const int nasosOtop;
    bool nasosOtopOn;  // Стан насосу опалення
    bool nasosOn;

  public:
    // Конструктор класу
    ControlSystem(int pinLow, int pinHigh, int nasosOtop) 
      : pinLow(pinLow), pinHigh(pinHigh), nasosOtop(nasosOtop), nasosOn(false) {}

    // Метод для ініціалізації пінів
    void initPins() {
        pinMode(pinLow, OUTPUT);
        pinMode(pinHigh, OUTPUT);
        pinMode(nasosOtop, OUTPUT);
        pinMode(Led_wifi, OUTPUT);
        pinMode(Led_power, OUTPUT);

        // Вимкнення всіх виходів на старті
        digitalWrite(pinLow, LOW);
        digitalWrite(pinHigh, LOW);
        digitalWrite(nasosOtop, LOW);
        digitalWrite(Led_wifi, LOW);
        digitalWrite(Led_power, HIGH);
    }

    // Метод для встановлення сигналу на насос опалення
    void nasosOtop_start(bool _nasosOtopOn) {
        nasosOtopOn = _nasosOtopOn;
    }

    // Перевірка стану насосів і керування ними
    void updateSystem() {
        if (nasosOtopOn) {
            turnNasosOn(); // Увімкнути насос опалення
        } else {
            turnNasosOff(); // Вимкнути насос опалення
        }
    }

    void led0n() {
        digitalWrite(Led_wifi, HIGH);
    }

    void led0ff() {
        digitalWrite(Led_wifi, LOW);
    }

    // Увімкнути насос опалення (Otop)
    void turnNasosOn() {
        digitalWrite(nasosOtop, HIGH);
        nasosOn = true;
        eeprom.nasos_on = true;
    }

    // Вимкнути насос опалення (Otop)
    void turnNasosOff() {
        digitalWrite(nasosOtop, LOW);
        nasosOn = false;
        eeprom.nasos_on = false;
    }

    // Підняти клапан
    void valveUp() {
        digitalWrite(pinHigh, HIGH);
        digitalWrite(pinLow, LOW);
    }

    // Зупинити підйом клапана
    void valveUpStop() {
        digitalWrite(pinHigh, LOW);
    }

    // Опустити клапан
    void valveDown() {
        digitalWrite(pinLow, HIGH);
        digitalWrite(pinHigh, LOW);
    }

    // Зупинити опускання клапана
    void valveDownStop() {
        digitalWrite(pinLow, LOW);
    }

    // Перевірити стан насосу опалення (Otop)
    bool isNasosOn() const {
        return nasosOn;
    }
};

// Приклад використання
ControlSystem control(PIN_LOW, PIN_HIGH, nasos_otop);  // пін-коди передаються через конструктор

void setup_out() {
    // Налаштування пінів
    control.initPins();
    
}

void loop_out() {
    // Оновлюємо стан насосів, перевіряючи сигнали
    control.updateSystem();
}
