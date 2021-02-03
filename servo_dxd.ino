#include <ESP32Servo.h>

Servo myservo; //declaration zone 
int servo_0 = 22; // ขาservo
int button_0 = 5; //ขาปุ่มกด
int ang = 0;

void setup()
{
  myservo.attach(servo_0); // D22 (กำหนดขาควบคุม Servo)
  pinMode(button_0,INPUT);
}
void loop()
{
 int button_0 = digitalRead(button_0);
 myservo.write(ang);
 if(button_0 == 0){
 for(ang = 0; ang < 180; ang++)
 {
  myservo.write(ang);
  delay(14);
 }
 }
 while(ang < 180){
  myservo.write(ang);
 }
}

void servo_open()
{
  myservo.write(0);
  delay(1000);
  myservo.write(90);
  delay(1000);
  myservo.write(180);
  delay(2000);
}

void servo_close()
{
  myservo.write(0);
  delay(1000);
}
