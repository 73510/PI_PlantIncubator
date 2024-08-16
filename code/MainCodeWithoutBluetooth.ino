/* #include <DHT.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#define DHTPIN 13
#define DHTTYPE DHT11

SoftwareSerial BTSerial(3,2);
DHT dht(DHTPIN,DHTTYPE);
byte buffer[1024];
int bufferPosition;
Servo playservo;
*/
/*핀번호*/
const int batterypin = 9; //서보 꽂은 핀
const int fanpin = 12; //선풍기 꽂은 핀
const int pumppin = 10; //펌프 꽂은 핀
const int ledpin = 11; //LED 꽂은 핀


int angle = 0; //서보 돌리는 각도                                            스프레이 일단 보류
//int spray_start = 50; //스프레이가동조건                                    스프레이 일단 보류
float hum; //습도값
float temp; //온도값
boolean ledtense = 0;
int fan_cnt = 0;
int fan_cntmove = 0;
int fan_t;
unsigned long LED_time1;
// void water(unsigned long pump_time); //waterspray함수와 waterpump전체를 제어하는 함수
// void waterpump(); //펌프 사용하는 함수
//void waterspray(float hum); //스프레이 제동하는 함수                 스프레이 일단 보류
void P_LED(); //LED 키고 끄는 함수
void P_LED_CONTROL(unsigned long LED_time1,unsigned long LED_time2);
void P_FAN();
void P_FAN_MOVE();
int t_cnt = 60*60*23 + 30;


void setup() {
  //BTSerial.begin(9600);
  Serial.begin(9600);
  //bufferPosition = 0;
  //playservo.attach(servoPin);
  // pinMode(servoPin,OUTPUT);
  pinMode(fanpin,OUTPUT);
  pinMode(pumppin,OUTPUT);
  pinMode(ledpin,OUTPUT);
  pinMode(batterypin,OUTPUT);
  digitalWrite(batterypin, LOW);
  digitalWrite(fanpin, HIGH);
  digitalWrite(pumppin, HIGH);
  digitalWrite(ledpin, HIGH);
  //playservo.write(angle);
  //spray_start = 50;                                                 스프레이 일단 보류
}

void loop() {
  /*
  hum = dht.readHumidity(); 
  temp = dht.readTemperature();
  if(BTSerial.available()) {
    byte data = BTSerial.read();
    BTSerial.println(data);
    Serial.write(BTSerial.read());
    switch(data) {
      case 0:
        //waterspray(hum);
        break;
      case 1:
        ledtense = 1;
        break;
      case 2:
        //spray_start++;                             스프레이 일단 보류
        break;
      case 3:
        //spray_start--;                             스프레이 일단 보류
        break;
      case 30:
        LED_time1 = 60*60*12; //12hr
        break;
      case 40:
        LED_time1 = 60*60*13;
        break;
    }
   water(hum);
   
  }
  if(Serial.available()){
    BTSerial.write(Serial.read());
  }
  */
  LED_time1 = 60*60*12; //12hr
  ledtense = 1;
  /*
  if (ledtense == 1) {
    if(t_cnt <= LED_time1){
      digitalWrite(ledpin, LOW);
    }
    else {
      digitalWrite(ledpin, HIGH);
    }
  }
  else {
    digitalWrite(ledpin, HIGH);
  }
*/
  if (t_cnt >= ((60*60*24) - 10)){
    if (t_cnt %2 == 0){
      digitalWrite(pumppin, LOW);
    }
    else {
      digitalWrite(pumppin, HIGH);
    }
  }
  else {
    digitalWrite(pumppin, HIGH);
  }

  if (t_cnt % (60*60) >= (60*55)){ // x:55 분에서 x+1:00 분 사이에 fan 가동 코드
    digitalWrite(pumppin, HIGH);
    digitalWrite(ledpin, HIGH);
    digitalWrite(batterypin, HIGH);
    digitalWrite(fanpin, LOW);
  }
  else {
    Serial.println("Off");
    digitalWrite(fanpin, HIGH);
    digitalWrite(ledpin, LOW);
  }
  /*
  if( 55 =< t_min <= 60) {
    digitalWrite(fanpin,LOW); 
    if(t_min == 60) {
      t_min = 0;
    }
  }
  if( t_cnt%60 == 0) {
    t_min++;
  }
  */
  t_cnt++;
  Serial.println(t_cnt);
  if (t_cnt == (60*60*24)){ //24시간에 한번씩 리셋
    Serial.println("reset");
    t_cnt = 0;
  }
  delay(8);
}

/*
void water(unsigned long pump_time) {
  
  if(hum <= spray_start) {
  waterspray(hum);
  }                                                     스프레이 일단 보류
  
  MsTimer2::set(pump_time, waterpump); 
  MsTimer2::start();
}

void waterpump() {
    digitalWrite(pumpPin,HIGH);
    delay(300);
    digitalWrite(pumpPin,LOW);
}

void waterspray(float hum)  {
     while(hum <= spray_start) {
        digitalWrite(servoPin,HIGH);
     }
}                                                  스프레이 일단 보류


void P_LED () { 
  if(LED_ONOFF == 0) {
    digitalWrite(ledPin,LOW);
    LED_ONOFF = 1;
  }
  else if(LED_ONOFF == 1) {
    digitalWrite(ledPin,HIGH);
    LED_ONOFF = 0;
  }
}

void P_FAN() {
  if(fan_cnt >= 6) {
    for(int i = 0 ; i < 10 ; i++); //이거 for문 필요없음
    {
      MsTimer2::set(1000,fan_move); //mstimer의 특성상 이거는 한번 넣어줘도 계속 1초 간격으로 fan_move 함수를 호출해
      MsTimer2::start;
      MsTimer2::set(1000,fan_move);// set이 한번 더나오면 그전에 있는 mstimer set은 리셋됨
      MsTimer2::start;
    }
    fan_cnt = 0;
  }
  else if(fan_cnt == 0) {
    P_FAN_MOVE() //끌때에도 fan_move 함수를 사용해야 되지 않을까?
  }
  fan_cnt++;
}


void P_FAN_MOVE () { 
  if(fan_cntmove == 0) {
    digitalWrite(fanPin,LOW);
    fan_cntmove = 1;
  }
  else if(fan_cntmove == 1) {
    digitalWrite(fanPin,HIGH);
    fan_cntmove = 0;
  }
}
*/

