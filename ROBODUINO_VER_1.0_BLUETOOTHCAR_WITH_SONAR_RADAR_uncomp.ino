#include "AMotor.h"
#include<SoftwareSerial.h>
#include <Servo.h>


unsigned long now,prev_sonar,prev_servo = 0;
unsigned long interval_sonar = 100;
unsigned long interval_servo = 100;

const int trigPin = 10;
const int echoPin = A0;
long duration;
int distanceCm;
Servo myservo;
int arr_val = 13;
int pos[] = {0,0,10,20,30,40,50,60,70,80,90,100,110};
int i,k = 0;

SoftwareSerial mySerial(2,13); // RX, TX
A_DCMotor FR(1,MOTOR12_1KHZ);
A_DCMotor FL(2,MOTOR12_1KHZ);
A_DCMotor BL(3,MOTOR34_1KHZ);
A_DCMotor BR(4,MOTOR34_1KHZ);

char command; 
int value;
void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
    mySerial.begin(9600);
    Serial.begin(9600);
    k = 1;

    myservo.attach(9);
    myservo.write(pos[5]);   
    
}

void loop() {
  // put your main code here, to run repeatedly:
      now = millis();

  while(mySerial.available() > 0){ 
    command = mySerial.read();     

    Serial.println(command);
    Stop(); //initialize with motors stoped
    //Change pin mode only if new command is different from previous.   
    //Serial.println(command);

    switch(command){
    case 'F':      
      forward(value);
      delay(50);
      break;
    case 'B':
       reverse(value);
       delay(50);
      break;
    case 'L':      
      left(value);
      delay(50);
      break;
    case 'R':      
      right(value);
      delay(50);
      break;
    case 'G':      
      frontleft(value);
      delay(50);
      break;
    case 'I':      
      frontright(value);
      delay(50);
      break;
     case 'H':      
      backleft(value);
      delay(50);
      break;
     case 'J':      
      backright(value);
      delay(50);
      break;
    case 'S':
       Stop();
       break;
    case '0':
      car_speed(0);
      break;
     case '1':
      car_speed(10);
      break;
    case '2':
      car_speed(20);
      break;
    case '3':
      car_speed(30);
      break;
    case '4':
      car_speed(40);
      break;
     case '5':
      car_speed(50);
      break;
     case '6':
      car_speed(60);
      break;
     case '7':
      car_speed(70);
      break;
     case '8':
      car_speed(80);
      break;
     case '9':
      car_speed(90);
      break;
     case 'q':
      car_speed(100);
      break;
     case 'D':
      Stop();
     break;
    
    }
  

  }
while((now - prev_sonar) >= interval_sonar)
  {
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distanceCm= duration*(0.034/2);
Serial.println(distanceCm);
if((now - prev_sonar) > 15){break;}
 prev_sonar = now;
}

if((now - prev_servo) >= interval_servo)
  {

    if(i == 12){ k = -1;}
    else if( i == 1){k = 1;}
    i = i + k;

  //  Serial.print(pos[i]);
  //    Serial.print("\n");

    myservo.write(pos[i]);
    prev_servo = now;
  }

  if(mySerial.available() < 0)
  {
    Stop();
  }

  // put your main code here, to run repeatedly:

}
  



void car_speed(int speed_t)
{
  value = map(speed_t,0,100,0,255);
}

void reverse(int Speed)
{
  FR.run(FORWARD);
  FR.setSpeed((Speed));
  FL.run(FORWARD);
  FL.setSpeed((Speed));
  BR.run(FORWARD);
  BR.setSpeed((Speed));
  BL.run(FORWARD);
  BL.setSpeed((Speed));  
}


void forward(int Speed)
{
  FR.run(BACKWARD);
  FR.setSpeed((Speed));
  FL.run(BACKWARD);
  FL.setSpeed((Speed));
  BR.run(BACKWARD);
  BR.setSpeed((Speed));
  BL.run(BACKWARD);
  BL.setSpeed((Speed));  
}


void right(int Speed)
{
    FR.run(FORWARD);
    FR.setSpeed((Speed));
    FL.run(BACKWARD);
    FL.setSpeed(int(Speed));
    BR.run(FORWARD);
    BR.setSpeed((Speed));
    BL.run(BACKWARD);
    BL.setSpeed(int(Speed));
}

void left(int Speed)
{
    FR.run(BACKWARD);
    FR.setSpeed((Speed));
    FL.run(FORWARD);
    FL.setSpeed((Speed));
    BR.run(BACKWARD);
    BR.setSpeed((Speed));
    BL.run(FORWARD);
    BL.setSpeed((Speed));
}

void backleft(int Speed)
{
    FR.run(FORWARD);
    FR.setSpeed((Speed)/2.2);
    FL.run(FORWARD);
    FL.setSpeed((Speed));
    BR.run(FORWARD);
    BR.setSpeed((Speed)/2.2);
    BL.run(FORWARD);
    BL.setSpeed((Speed));
}
void backright(int Speed)
{
    FR.run(FORWARD);
    FR.setSpeed((Speed));
    FL.run(FORWARD);
    FL.setSpeed((Speed)/1.8);
    BR.run(FORWARD);
    BR.setSpeed((Speed));
    BL.run(FORWARD);
    BL.setSpeed((Speed)/1.8);
}
void frontright(int Speed)
{
    FR.run(BACKWARD);
    FR.setSpeed((Speed)/1.8);
    FL.run(BACKWARD);
    FL.setSpeed((Speed));
    BR.run(BACKWARD);
    BR.setSpeed((Speed)/1.8);
    BL.run(BACKWARD);
    BL.setSpeed((Speed));
}
void frontleft(int Speed)
{
    FR.run(BACKWARD);
    FR.setSpeed((Speed));
    FL.run(BACKWARD);
    FL.setSpeed((Speed)/2.2);
    BR.run(BACKWARD);
    BR.setSpeed((Speed));
    BL.run(BACKWARD);
    BL.setSpeed((Speed)/2.2);
}



void Stop()
{
    FR.run(RELEASE);
    FR.setSpeed(0);
    FL.run(RELEASE);
    FL.setSpeed(0);
    BR.run(RELEASE);
    BR.setSpeed(0);
    BL.run(RELEASE);
    BL.setSpeed(0);
}
