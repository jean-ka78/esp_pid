

void ConnectWIFI() {
  // Запускаем WiFi
  if (WiFi.status() != WL_CONNECTED) { // Если нет WiFi, то коннектимся
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASS);

    int8_t count = 0;
    while (WiFi.status() != WL_CONNECTED && count < 50) { // Уменьшено количество попыток до 50
      delay(100);
      Serial.print(".");
      count++;
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("WiFi connected");
      Serial.println(WiFi.localIP());
      
    } else {
      Serial.println("WiFi not connected");
      WiFi.disconnect(); // Отключаемся от сети
      
    }
  } else {
    Serial.println("Already connected to WiFi");
    Serial.println(WiFi.localIP());
    
    
  }
}

