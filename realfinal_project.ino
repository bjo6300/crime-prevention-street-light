#include <SoftwareSerial.h> // 블루투스 시리얼통신 라이브러리 호출
#include <LiquidCrystal_I2C.h> // LCD 라이브러리
#include <MsTimer2.h>
#include <TimeLib.h>
#include "pitches.h" // tone() 헤더파일

LiquidCrystal_I2C lcd(0x27, 16, 2); // lCD 설정

int delayflag = 0; // 0이면 시간, 1이면 가로등 아이디
int before = 0;
// 조도 센서 변수
float total = 0.0;
float avg = 0.0;
// 블루투스
int blueTx=2;   //Tx (보내는핀 설정)at
int blueRx=3;   //Rx (받는핀 설정)
SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언
int switchflag = 0; // 스위치 flag
int switchmode = 0; // 스위치 모드
const int sensorMin = 0; // 화재감지 변수
const int sensorMax = 1024; // 화재감지 변수

// 시간, 가로등 모드 변경
void change_mode()
{
  if (delayflag) {
    before = 1;
    delayflag = 0;
  }
  else {
    before = 0;
    delayflag = 1;
  }
}

// 사이렌 소리 및 LED red 깜빡이기
void SOS_sound(){
  analogWrite(10,0);
  for(int i=0;i<2;i++){
    
            for (int hz = 300; hz <= 750; hz++)
          {
            tone(8, hz);
            
            delay(5);

            if(hz == 300){
              analogWrite(9,0);            
            }
            if(hz == 450){
              analogWrite(9,255);            
            }
            if(hz == 600){
              analogWrite(9,0);            
            }
            if(hz == 750){
              analogWrite(9,255);            
            }
          }
          
          for (int hz = 750; hz >= 300; hz--)
          {
            if(hz == 750){
              analogWrite(9,255);            
            }
            if(hz == 600){
              analogWrite(9,0);            
            }
            if(hz == 450){
              analogWrite(9,255);            
            }
            if(hz == 300){
              analogWrite(9,0);            
            }
            tone(8, hz);
        
            delay(5);
          }
          analogWrite(9,0);
          delay(100);
        }
  analogWrite(9,0);
  
}

void setup() 
{
  Serial.begin(9600);   //시리얼모니터
  mySerial.begin(9600); //블루투스 시리얼

  setTime(10,20,12,17,12,2021); // LCD 시간 설정
  
  //LED R=9, G=10, B=11
  for(int i=9; i<12; i++){
    pinMode(i,OUTPUT);
  }
  
  // LCD
  lcd.begin();
  lcd.backlight();

  // Timer Inturrupt
  MsTimer2::set(5000, change_mode);
  MsTimer2::start();

  lcd.clear();

  // 블루투스 시리얼
  SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언

  // 스위치 버튼
  pinMode(4,INPUT_PULLUP);
  pinMode(4,OUTPUT);

  // 수동 부저
  pinMode(8,OUTPUT);
}

void loop()
{
  
  // 타이머
  time_t t = now();

  // 화재감지
  int sensorReading = analogRead(A1);
  Serial.println(sensorReading);
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);
  Serial.println(range);
    switch(range){
    case 0:
      Serial.println("** Close Fire **");
      break;
    case 1:
      Serial.println("** Distant Fire **");
      // 블루투스 송신
      mySerial.println("Fire from JJ1718");         

      // lcd 표시
      lcd.clear();
      lcd.setCursor(5,0); // LCD 맨윗줄
      lcd.print("Fire!!!");
      lcd.setCursor(5,1); // LCD 맨윗줄
      lcd.print("Fire!!!");
      
      for(int i=0;i<1;i++){
         // SOS 소리 & LED 깜빡임
         SOS_sound();
      }
      noTone(8);
      
      break;
    case 2:
      Serial.println("No Fire");
      break;
    }
    delay(1);
  
  // 평소 LED + 조도센서
  if(switchmode == 0){
    analogWrite(9,0);
    analogWrite(11,0);

    int a = analogRead(A0);
    int bright = map(a,0,1023,0,255); // 밝기
//    Serial.println(bright);
    
    if (bright > 100)
      bright = 0;
    
    else if(bright < 120){
      bright = 255;
    }
    analogWrite(10,bright);
  }

  // 스위치 누를때
  int switchVal = digitalRead(4); // 4번 핀 버튼 입력 값 받기
  
  if(switchVal == LOW){
    
    switchmode = 1; // 스위치 킨 모드
    switchflag++;
    
    // lcd 표시
    lcd.clear();
    lcd.setCursor(5,0); // LCD 맨윗줄
    lcd.print("SOS!!!");
    lcd.setCursor(5,1); // LCD 맨윗줄
    lcd.print("SOS!!!");
    
    if(switchmode == 1 && switchflag == 1){
        mySerial.println("SOS from JJ1718"); // SOS 블루투스 송신
        for(int i=0;i<1;i++){
           // SOS 소리, led 깜빡임
           SOS_sound();
        }
        noTone(8);

      }
    delay(300);
    lcd.clear();  
  }

  // 일반모드 (평소모드)
  if(switchVal == HIGH){
    if(switchflag >= 2){ 
      noTone(8);
      analogWrite(9,0);
      analogWrite(11,0);
      switchflag = 0;
    }
    switchmode = 0;
    delay(300);
  }
  
  total = 0.0; // 초기화

  if (before != delayflag)
    lcd.clear();
  
  // 현재 시간
  if(delayflag == 0){
    before = 0;
    lcd.setCursor(3,0); // LCD 맨윗줄
    lcd.print(year(t));
    lcd.print("/");
    lcd.print(month(t));
    lcd.print("/");
    lcd.print(day(t));
    
    lcd.setCursor(4,1); // LCD 맨 아래줄
  
    lcd.print(hour(t));
    lcd.print(":");
    lcd.print(minute(t));
    lcd.print(":");
    lcd.print(second(t));
  }
  
  // 가로등 아이디
  else if(delayflag == 1){
    before = 1;
    lcd.setCursor(5,0); // LCD 맨 윗줄
    lcd.print("lamp ID");
    lcd.setCursor(5,1); // LCD 맨 아래줄
    lcd.print("JJ1718");
  }
  
}
