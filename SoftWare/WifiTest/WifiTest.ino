// #include <WiFi.h>


// 1st, for AP mode

// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600);
//   WiFi.softAP("ESP32_TEST","12345678");
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   Serial.print("当前连接热点设备数量:");
//   Serial.println(WiFi.softAPgetStationNum()); // 打印当前连接设备数量
//   delay(1000);
// }


// 2nd, for STA mode

// void setup()
// {
//   Serial.begin(9600);
//   WiFi.mode(WIFI_STA);
//   Serial.println("Wifi connecting");
//   WiFi.begin("ESP32_TEST","12345678");
//   while(WiFi.status() != WL_CONNECTED)
//   {
//     delay(1000);
//     Serial.print(".");
//   }
//   Serial.print("\n");
//   Serial.println("Connected!");
// }

// void loop(){
//   Serial.println("WIFI Connected!");
//   Serial.print("IP Addr.  :");
//   Serial.println(WiFi.localIP());
// }


// next code is for N to 1 communication(maybe 1 to 1 or 2 to 1 communication)
// using espnow library

// prerequisites: get each boards MAC address
#ifdef ESP32
  #include <WiFi.h>
  #include <esp_wifi.h>
#else
  #include <ESP8266WiFi.h>
#endif

void setup()
{
  Serial.begin(115200);

  Serial.print("ESP Board MAC Address:");
  #ifdef ESP32
    WiFi.mode(WIFI_STA);
    WiFi.STA.begin();
    uint8_t baseMac[6];
    esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA,baseMac);
    if(ret==ESP_OK)
    {
      Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
                    baseMac[0],baseMac[1],baseMac[2],
                    baseMac[3],baseMac[4],baseMac[5]);
    }
    else
    {
      Serial.println("Failed to read MAC address");
    }
  #else // 8266 board
    Serial.println(WiFi.macAddress());
  #endif
}
void loop()
{}
// get MAC Addr. log:
// esp32 board: c0:5d:89:b0:e6:ac
// esp8266 board_1: A8:48:FA:DC:59:0C
// esp8266 board_2: A8:48:FA:DC:CF:13 (maybe no use?)

