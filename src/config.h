//MQTT Server
const char *mqtt_server = "192.168.10.250"; // Имя сервера MQTT
const int mqtt_port = 1883; // Порт для подключения к серверу MQTT
const char *mqtt_user = "mqtt"; // Логин от сервер
const char *mqtt_pass = "qwerty"; // Пароль от сервера
// Pins relay
const int RELAY_LOW  = 12;  // GPIO12
const int RELAY_HIGH = 5;   // GPIO5
const int RELAY_NASOS = 13;  // GPIO2
const int LED = 2;         // GPIO13
const int POWER = 14; // GPI14




// #define WIFI_SSID "aonline"  // Имя точки доступа WIFI
// #define WIFI_PASS "1qaz2wsx3edc" // Пароль точки доступа WIFI

#define WIFI_SSID "Keenetic-2349"  // Имя точки доступа WIFI
#define WIFI_PASS "10021963" // Пароль точки доступа WIFI
// Data wire is plugged into GPIO 9 on the ESP
#define ONE_WIRE_BUS 9 //9