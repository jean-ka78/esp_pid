const int PIN_LOW = 12; // Заміна pin_low на gpio12
const int PIN_HIGH = 3;// Заміна pin_high на gpio03
const int nasos_otop = 0; // Заміна nasos_otop на gpio0

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
      : pinLow(pinLow), pinHigh(pinHigh), nasosOtop(nasosOtop), nasosOn(false) {
        // Ініціалізація пінів під час створення об'єкта
        pinMode(pinLow, OUTPUT);
        pinMode(pinHigh, OUTPUT);
        pinMode(nasosOtop, OUTPUT);
    }

    // Метод для встановлення сигналу на насос опалення
    void nasosOtop_start(bool _nasosOtopOn){
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
        digitalWrite(pinHigh, LOW);
        digitalWrite(pinLow, HIGH);
    }

    // Зупинити підйом клапана
    void valveUpStop() {
        digitalWrite(pinHigh, HIGH);
    }

    // Опустити клапан
    void valveDown() {
        digitalWrite(pinLow, LOW);
        digitalWrite(pinHigh, HIGH);
    }

    // Зупинити опускання клапана
    void valveDownStop() {
        digitalWrite(pinLow, HIGH);
    }

    // Перевірити стан насосу опалення (Otop)
    bool isNasosOn() const {
        return nasosOn;
    }
};

// Приклад використання
ControlSystem control(PIN_LOW, PIN_HIGH, nasos_otop);  // пін-коди передаються через конструктор

void setup_out() {
    // Налаштування пінів виконується в конструкторі, тому setup() пустий
}

void loop_out() {
    // Оновлюємо стан насосів, перевіряючи сигнали
    control.updateSystem();
}
