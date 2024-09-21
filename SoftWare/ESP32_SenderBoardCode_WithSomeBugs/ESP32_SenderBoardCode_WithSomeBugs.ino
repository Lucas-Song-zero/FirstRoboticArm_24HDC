#include <esp_now.h>
#include <WiFi.h>
#include <SimpleKalmanFilter.h>

#define Sensor1 33
#define Sensor2 32
#define Sensor3 35

uint8_t RecAddr[] = {0xA8,0x48,0xFA,0xDC,0xCF,0x13}; // receiver's MAC address

esp_now_peer_info_t peerInfo;

typedef struct SendFrom32
{
  int FingerAngles[3];
} SendFrom32;
SendFrom32 dataFrom32;  // data to be sent

void setup()
{
  Serial.begin(9600);
  // pinMode(27,INPUT);
  // pinMode(26,INPUT);
  // pinMode(25,INPUT);
  // pinMode(33,INPUT);
  // pinMode(32,INPUT);
  // pinMode(35,INPUT);
  // pinMode()
  pinMode(Sensor1, INPUT);
  pinMode(Sensor2, INPUT);
  pinMode(Sensor3, INPUT);

  WiFi.mode(WIFI_STA);
  if(esp_now_init() != ESP_OK)
  {
    Serial.println("Error Init EPSNOW");
    return;
  }
  // esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, RecAddr, sizeof(RecAddr));
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if(esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("failed to add peer");
    return;
  }
}

void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status)
{

}


int transform(int index,uint16_t v)
{
  switch(index)
  {
    case 1:
      return (v >= 2500) ? 0 : ((v <= 1800) ? 90 : -1); // -1 表示无效值
      break;

    case 3:
      return (v >= 3000) ? 0 : ((v <= 1500) ? 90 : -1); // -1 表示无效值
      break;
  
    case 5:
      return (v >= 3800) ? 0 : ((v <= 2500) ? 90 : -1); // -1 表示无效值
      break;
  }
  return -1; // 对于无效的索引返回-1
}

void loop()
{
  Serial.printf("1:%d\n",analogRead(33));
  Serial.printf("3:%d\n",analogRead(32));
  Serial.printf("5:%d\n",analogRead(35));

  delay(100);

  dataFrom32.FingerAngles[0] = transform(1, analogRead(33));
  dataFrom32.FingerAngles[1] = transform(3, analogRead(32));
  dataFrom32.FingerAngles[2] = transform(5, analogRead(35));

  delay(150);
  
  for(int i=0;i<3;++i)
  {
    Serial.printf("FingerAnlges[%d]:%d\n",i,dataFrom32.FingerAngles[i]);
  }
  
  esp_err_t res = esp_now_send(RecAddr, (uint8_t*)&dataFrom32, sizeof(dataFrom32));
  delay(100);
}
