#include <Servo.h>
#include <Wire.h>
#include <SPI.h>
#include <RTClib.h>
#include <TridentTD_LineNotify.h>

#define SSID        "500buck"      // บรรทัดที่ 7 ให้ใส่ ชื่อ Wifi ที่จะเชื่อมต่อ
#define PASSWORD    "123456789"     // บรรทัดที่ 8 ใส่ รหัส Wifi
#define LINE_TOKEN  "ROin2dNqMDCiJVik0HOxfq04l5ASs7Fxlmop6k3Wfp0"   // บรรทัดที่ 9 ใส่ รหัส TOKEN ที่ได้มาจากข้างบน


RTC_DS3231 RTC;

Servo myservo;

#define servoPin  D5

#define trigPin D7
#define echoPin D6
//const int buttonPin = D6;
//#define ledPin  D7

int count_notify;
int lasthour;
long duration, distance;

void setup() {
    int lasthour = 0 ;

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Wire.begin();
  RTC.begin();
  RTC.adjust(DateTime(__DATE__, __TIME__)); 

  Serial.begin(115200); 
  Serial.println();
  Serial.println(LINE.getVersion());

  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());

  // กำหนด Line Token
  LINE.setToken(LINE_TOKEN);

  DateTime now = RTC.now();
  //pinMode(buttonPin,INPUT);
}

void loop() {

  DateTime now = RTC.now();

 /* if(count_notify >= 32){
    count_notify = 0;
  }*/

  /*Serial.print(count_notify);
  Serial.println();
  delay(100);*/


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
  Serial.print(lasthour);
  Serial.println("AM");

if(distance >= 10 && distance <=18 && lasthour != now.hour())
{
  LINE.notify("อาหารใกล้หมด กรุณาเติม");
  delay(1000);
  lasthour = now.hour();
}


  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour());
  Serial.print(':');
  Serial.print(now.minute());
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  if (now.hour() == 8 && now.minute() == 5 && now.second() == 0){
  //if(digitalRead(buttonPin) == HIGH){
    myservo.attach(servoPin);
    myservo.write(0);
    delay(165);
    myservo.write(90);
    delay(100);
    myservo.write(180);
    delay(300);
    myservo.write(90);
    delay(1000);
  }
  else if (now.hour() == 15 && now.minute() == 19){
  //if(digitalRead(buttonPin) == HIGH){
    myservo.attach(servoPin);
    myservo.write(0);
    delay(1000);
    myservo.write(90);
    delay(10);
    myservo.write(180);
    delay(660);
    myservo.write(90);
    delay(60000);
  }
  else if (now.hour() == 18 && now.minute() == 5 && now.second() == 0){
  //if(digitalRead(buttonPin) == HIGH){
    myservo.attach(servoPin);
    myservo.write(0);
    delay(500);
    myservo.write(90);
    delay(10);
    myservo.write(180);
    delay(660);
    myservo.write(90);
    delay(1000);
  }
  else{
    myservo.write(90);
    delay(1000);
    //count_notify++;
  }
  delay(100);
}

long microsecondsToCentimeters(long microseconds)
{
// ความเร็วเสียงในอากาศประมาณ 340 เมตร/วินาที หรือ 29 ไมโครวินาที/เซนติเมตร
// ระยะทางที่ส่งเสียงออกไปจนเสียงสะท้อนกลับมาสามารถใช้หาระยะทางของวัตถุได้
// เวลาที่ใช้คือ ระยะทางไปกลับ ดังนั้นระยะทางคือ ครึ่งหนึ่งของที่วัดได้
return microseconds / 29 / 2;
}
