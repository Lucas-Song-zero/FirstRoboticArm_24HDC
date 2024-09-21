#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x41);
#define Deg_0 102
#define Deg_10 114
#define Deg_20 134
#define Deg_30 155
#define Deg_40 176
#define Deg_45 187
#define Deg_50 197
#define Deg_60 218
#define Deg_70 239
#define Deg_75 249
#define Deg_80 259
#define Deg_90 280
#define Deg_100 301
#define Deg_110 321
#define Deg_120 342
#define Deg_130 363
#define Deg_140 383
#define Deg_150 398
#define Deg_160 425
#define Deg_170 446
#define Deg_180 510 
#define INT 4

static int mode = 1; // 0--跟随模式; 1--自动演示模式; 2--K210连接模式
static String comdata = ""; // 接受从K210收集到的数据
uint32_t timeCur = 0;
int fingerangles[3];
bool recData = false;

typedef struct FromESP32
{
  int FingerAngles[3]; // 10个手指关节对应的角度，从大拇指根开始0,大拇指第二个关节1,食指根2,依次到小拇指第二个关节9
} FromESP32;
FromESP32 from32;

typedef struct From8266
{
  int id;
  int shape;
} From8266;
From8266 from8266;

void OnDataRecv(uint8_t* mac_addr, uint8_t* incomingData, uint8_t len)
{
  memcpy(&from32, incomingData, sizeof(from32));
  Serial.printf("1:%d  2:%d  3:%d\n",from32.FingerAngles[0],from32.FingerAngles[1],from32.FingerAngles[2]);
  recData = true;
}

void OnDataRecv2(uint8_t* mac_addr, uint8_t* incomingData, uint8_t len)
{
  memcpy(&from8266, incomingData, sizeof(from8266));
  Serial.printf("Recv: %d\n",from8266.shape);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);

  // set the Interrupt Pin
  pinMode(INT, INPUT_PULLUP);
  attachInterrupt(INT, isr, FALLING); // 配置INT(4号引脚)在按下按钮(下降沿)将MODE切换

  // Init ESP-NOW
  if(esp_now_init()!= 0)
  {
    Serial.println("Error Init ESP-NOW");
    return;
  }
  // After ESP-NOW Init is Done, register for recv CB to get recv Packer Info
  // esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));

  // only for test
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);// 50HZ更新频率，相当于20ms的周期
  pwm1.begin();
  pwm1.setPWMFreq(50);// 50HZ更新频率，相当于20ms的周期
  delay(100);
}

void five()//完全张开//五
{pwm.setPWM(1, 0, Deg_50);//拇指根
pwm.setPWM(6, 0, Deg_140);//拇指中
pwm.setPWM(8, 0, Deg_130);//拇指前
pwm.setPWM(2, 0, Deg_150);//食指根
pwm.setPWM(4, 0, Deg_170);//食指中
pwm.setPWM(3, 0, Deg_10);//中指中
pwm.setPWM(0, 0, Deg_120);//中指根
pwm.setPWM(7, 0, Deg_40);//无名中
pwm.setPWM(5, 0, Deg_50);//无名根
pwm.setPWM(9, 0, Deg_0);//小指
}

void one()//一
{pwm.setPWM(1, 0, Deg_180);//拇指根
pwm.setPWM(6, 0, Deg_100);//拇指中
pwm.setPWM(8, 0, Deg_100);//拇指前
pwm.setPWM(2, 0, Deg_150);//食指根
pwm.setPWM(4, 0, Deg_170);//食指中
pwm.setPWM(3, 0, Deg_120);//中指中
pwm.setPWM(0, 0, Deg_30);//中指根
pwm.setPWM(7, 0, Deg_160);//无名中
pwm.setPWM(5, 0, Deg_130);//无名根
pwm.setPWM(9, 0, Deg_180);//小指
}

void two()//二
{pwm.setPWM(1, 0, Deg_180);//拇指根
pwm.setPWM(6, 0, Deg_100);//拇指中
pwm.setPWM(8, 0, Deg_100);//拇指前
pwm.setPWM(2, 0, Deg_150);//食指根
pwm.setPWM(4, 0, Deg_170);//食指中
pwm.setPWM(3, 0, Deg_10);//中指中
pwm.setPWM(0, 0, Deg_120);//中指根
pwm.setPWM(7, 0, Deg_160);//无名中
pwm.setPWM(5, 0, Deg_130);//无名根
pwm.setPWM(9, 0, Deg_180);//小指
}

void three()//三
{pwm.setPWM(1, 0, Deg_180);//拇指根
pwm.setPWM(6, 0, Deg_100);//拇指中
pwm.setPWM(8, 0, Deg_100);//拇指前
pwm.setPWM(2, 0, Deg_150);//食指根
pwm.setPWM(4, 0, Deg_170);//食指中
pwm.setPWM(3, 0, Deg_10);//中指中
pwm.setPWM(0, 0, Deg_120);//中指根
pwm.setPWM(7, 0, Deg_40);//无名中
pwm.setPWM(5, 0, Deg_50);//无名根
pwm.setPWM(9, 0, Deg_180);//小指
}
void four()//四
{pwm.setPWM(1, 0, Deg_180);//拇指根
pwm.setPWM(6, 0, Deg_100);//拇指中
pwm.setPWM(8, 0, Deg_100);//拇指前
pwm.setPWM(2, 0, Deg_150);//食指根
pwm.setPWM(4, 0, Deg_170);//食指中
pwm.setPWM(3, 0, Deg_10);//中指中
pwm.setPWM(0, 0, Deg_120);//中指根
pwm.setPWM(7, 0, Deg_40);//无名中
pwm.setPWM(5, 0, Deg_50);//无名根
pwm.setPWM(9, 0, Deg_0);//小指
}
void six()//六
{pwm.setPWM(1, 0, Deg_40);//拇指根
pwm.setPWM(6, 0, Deg_140);//拇指中
pwm.setPWM(8, 0, Deg_130);//拇指前
pwm.setPWM(2, 0, Deg_40);//食指根
pwm.setPWM(4, 0, Deg_70);//食指中
pwm.setPWM(3, 0, Deg_120);//中指中
pwm.setPWM(0, 0, Deg_30);//中指根
pwm.setPWM(7, 0, Deg_160);//无名中
pwm.setPWM(5, 0, Deg_130);//无名根
pwm.setPWM(9, 0, Deg_0);//小指
}
void thumb()//大拇指
{pwm.setPWM(1, 0, Deg_40);//拇指根
pwm.setPWM(6, 0, Deg_140);//拇指中
pwm.setPWM(8, 0, Deg_130);//拇指前
pwm.setPWM(2, 0, Deg_40);//食指根
pwm.setPWM(4, 0, Deg_70);//食指中
pwm.setPWM(3, 0, Deg_120);//中指中
pwm.setPWM(0, 0, Deg_30);//中指根
pwm.setPWM(7, 0, Deg_160);//无名中
pwm.setPWM(5, 0, Deg_130);//无名根
pwm.setPWM(9, 0, Deg_180);//小指
}
void fuck()//中指
{pwm.setPWM(1, 0, Deg_180);//拇指根
pwm.setPWM(6, 0, Deg_100);//拇指中
pwm.setPWM(8, 0, Deg_100);//拇指前
pwm.setPWM(2, 0, Deg_40);//食指根
pwm.setPWM(4, 0, Deg_70);//食指中
pwm.setPWM(3, 0, Deg_10);//中指中
pwm.setPWM(0, 0, Deg_120);//中指根
pwm.setPWM(7, 0, Deg_160);//无名中
pwm.setPWM(5, 0, Deg_130);//无名根
pwm.setPWM(9, 0, Deg_180);//小指
}

void SETPWM(Adafruit_PWMServoDriver pwm,int port,int initdeg,int finaldeg)//调整手臂关节
{int i=0;
if(initdeg>finaldeg)
{
  for(i=initdeg;i>finaldeg;i--)
  {
    pwm.setPWM(port,0,i);
    delay(5);
  }
}
else
{
  for(i=initdeg;i<finaldeg;i++)
  {
    pwm.setPWM(port,0,i);
    delay(5);
  }
}

}
IRAM_ATTR void isr()
{
  mode = (mode+1)%3;
}

void Follow()
{
  
  // from32是通过wifi获得的数据,内存的数据格式详情参见前面的定义
  int angles[3];
  if(recData) // 接受到数据,可以更新一次角度值
  {
    for(int i=0;i<3;++i)
    {
      angles[i]=from32.FingerAngles[i];
    }
    // 下面是角度控制
    if(angles[0]==90)
    {
      pwm.setPWM(2, 0, Deg_40);//食指根
      pwm.setPWM(4, 0, Deg_70);//食指中
    }
    else 
    {
      pwm.setPWM(2, 0, Deg_130);//食指根
      pwm.setPWM(4, 0, Deg_170);//食指中
    }
    if(angles[1]==90)
    {
      pwm.setPWM(0, 0, Deg_30);//中指根
      pwm.setPWM(3, 0, Deg_120);//中指中
    }
    else 
    {
      pwm.setPWM(0, 0, Deg_120);//中指根
      pwm.setPWM(3, 0, Deg_10);//中指中
    }
    if(angles[2]==90)
    {
      pwm.setPWM(1, 0, Deg_180);//拇指根
      pwm.setPWM(7, 0, Deg_160);//无名中
      pwm.setPWM(5, 0, Deg_130);//无名根
      pwm.setPWM(9, 0, Deg_180);//小指
    }
    else 
    {
      pwm.setPWM(1, 0, Deg_40);//拇指根
      pwm.setPWM(7, 0, Deg_40);//无名中
      pwm.setPWM(5, 0, Deg_50);//无名根
      pwm.setPWM(9, 0, Deg_0);//小指
    }

    // 下面是把recData设为false，等待下一次接受数据
    recData=false;
  }
  
 
  delay(1000);

}

void AutoDisplay()
{
  // 自动展示一些动作
  
  SETPWM(pwm1,1,Deg_70,Deg_10);
  pwm1.setPWM(8,0,Deg_0);
  delay(1500);
  // thumb();
  // delay(2000);
  one();
  delay(2000);
  two();
  delay(2000);
  three();
  delay(2000);
  four();
  delay(2000);
  five();
  delay(2000);
  six();
  delay(2000);
  five();
  SETPWM(pwm1,1,Deg_10,Deg_70);
  pwm1.setPWM(8,0,Deg_90);
  delay(2000);

}

void K210Link()
{
  // 和K210连接,接受信号
  while(1)
  {
    Serial.printf("Shape:%d",from8266.shape);

    switch(from8266.shape)
    {
      case 0:
      {
        fuck();
        break;
      }

      case 1:
      {
        five();
        delay(3000);
        one();
        break;
      }

      case 2:
      {
        two();
        break;
      }

      case 3:
      {
        four();
        delay(500);
        three();
        break;
      }

      case 4:
      {
        four();
        break;
      }

      case 5:
      {
        five();
        break;
      }

      case 6:
      {
        six();
        break;
      }

      case 7: // thumb
      {
        thumb();
        break;
      }

      case 8: // gun
      {
        break;
      }

      case 9: // pink
      {
        break;
      }
    }
  delay(3000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
    mode=0;

  switch(mode)
  {
    case 0:
    {
      esp_now_register_recv_cb(OnDataRecv);
      Follow();
      break;
    }

    case 1:
    {
      AutoDisplay();
      break;
    }

    case 2:
    {
      esp_now_register_recv_cb(OnDataRecv2);
      pwm1.setPWM(1,0,Deg_10);
      pwm1.setPWM(8,0,Deg_0);
      five();
      delay(3000);
      K210Link();
      break;
    }
    default:
    {
      Serial.println("Wrong Mode!");
    }
  }
}

