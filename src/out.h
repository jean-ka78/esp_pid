class RelayController {
    private:
        int relayLow;
        int relayHigh;
        int relayNasos;
        int led;
        int power;
    
    public:
        RelayController(int low, int high, int nasos, int ledPin, int power_pin) {
            relayLow = low;
            relayHigh = high;
            relayNasos = nasos;
            led = ledPin;
            power = power_pin;
        }
    
        void begin() {
            pinMode(relayLow, OUTPUT);
            pinMode(relayHigh, OUTPUT);
            pinMode(relayNasos, OUTPUT);
            pinMode(led, OUTPUT);
            pinMode(power, OUTPUT);
            
            // Отключаем реле при старте (если реле с логикой LOW)
            digitalWrite(relayLow, LOW);
            digitalWrite(relayHigh, LOW);
            digitalWrite(relayNasos, LOW);
            digitalWrite(led, LOW);
            digitalWrite(power, HIGH);
        }
    
        void setRelayLow(bool state) {
            digitalWrite(relayLow, state ? LOW : HIGH);
            if (state) {
                setRelayHigh(false);
            }
        }
    
        void setRelayHigh(bool state) {
            digitalWrite(relayHigh, state ? LOW : HIGH);
            if (state) {
                setRelayLow(false);
            }
        }
    
        void setRelayNasos(bool state) {
            digitalWrite(relayNasos, state ? LOW : HIGH);
        }
    
        void setLed(bool state) {
            digitalWrite(led, state ? HIGH : LOW);
        }
    };
    
    // Использование класса
    RelayController relayController(RELAY_LOW, RELAY_HIGH, RELAY_NASOS, LED, POWER);

void setup_out() {
    // Налаштування пінів
    relayController.begin();    
}

void loop_out() {
    // Оновлюємо стан насосів, перевіряючи сигнали
   
}
