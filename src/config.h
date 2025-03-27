//MQTT Server
const char *mqtt_server = "192.168.10.250"; // Имя сервера MQTT
const int mqtt_port = 1883; // Порт для подключения к серверу MQTT
const char *mqtt_user = "mqtt"; // Логин от сервер
const char *mqtt_pass = "qwerty"; // Пароль от сервера
const int PIN_LOW = 12; // Заміна pin_low на gpio12
const int PIN_HIGH = 5;// Заміна pin_high на gpio05
const int nasos_otop = 2; // Заміна nasos_otop на gpio2
const int Led_wifi = 13; //  Led_wifi на gpio13иву выкочу
const int Led_power = 14; //  Led_wifi на gpio14
// #define WIFI_SSID "aonline"  // Имя точки доступа WIFI
// #define WIFI_PASS "1qaz2wsx3edc" // Пароль точки доступа WIFI

#define WIFI_SSID "Keenetic-2349"  // Имя точки доступа WIFI
#define WIFI_PASS "10021963" // Пароль точки доступа WIFI
// Data wire is plugged into GPIO 9 on the ESP
#define ONE_WIRE_BUS 9