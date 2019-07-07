
/* подключение библиотек. недостающие необходимо скачать через ардуино*/
#include <IRremote.h>
#include <RobotIRremote.h>
#include <RobotIRremoteTools.h>
#include <ArduinoRobot.h>
#include <Wire.h>


/* пин IR сенсора*/
int IRsensorPin = 12;

/* define the some functions used by the library */
IRrecv irrecv(IRsensorPin);
decode_results results;

/* задаём пины для мотора L298N  */
int RightMotorForward = 7;    // IN1
int RightMotorBackward = 6;   // IN2
int LeftMotorForward = 5;     // IN3
int LeftMotorBackward = 4;    // IN4


void setup(){
  
  /* initialize motor control pins as output */
  pinMode(LeftMotorForward,OUTPUT);
  pinMode(RightMotorForward,OUTPUT);
  pinMode(LeftMotorBackward,OUTPUT);
  pinMode(RightMotorBackward,OUTPUT);

  /* start serial communication to see hex codes */
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop(){
  
  /* if the sensor is receive any signal */
  if (irrecv.decode(&results)){
    
    /* print the hex code value on the serial monitor */
    Serial.println(results.value);
    delay(5);

    /* resume function according to hex code */
    irrecv.resume();
  }
  
  /* if the incoming data is "defined hex code" then run the motors functions */
  /* instead of zeros "0000", write the hex codes of your remote control */
  if(results.value == 0xFF18E7) MotorForward(); /*хекс коды берем из файла hex_read. направляем пульт на ir сенсор и считываем код нажатой клавиши. */
  if(results.value == 0xFF4AB5) MotorBackward();
  if(results.value == 0xFF10EF) TurnRight();
  if(results.value == 0xFF5AA5) TurnLeft();
  if(results.value == 0xFF38C7) MotorStop();
  
}

/* FORWARD */
void MotorForward(){
  digitalWrite(LeftMotorForward,HIGH);
  digitalWrite(RightMotorForward,HIGH);
  digitalWrite(LeftMotorBackward,LOW);
  digitalWrite(RightMotorBackward,LOW); 
}

/* BACKWARD */
void MotorBackward(){
  digitalWrite(LeftMotorBackward,HIGH);
  digitalWrite(RightMotorBackward,HIGH);
  digitalWrite(LeftMotorForward,LOW);
  digitalWrite(RightMotorForward,LOW);
}

/* TURN RIGHT */
void TurnRight(){
  digitalWrite(LeftMotorForward,HIGH); 
  digitalWrite(RightMotorForward,LOW);
  digitalWrite(LeftMotorBackward,LOW);
  digitalWrite(RightMotorBackward,HIGH);
}

/* TURN LEFT */
void TurnLeft(){
  digitalWrite(RightMotorForward,HIGH);  
  digitalWrite(LeftMotorForward,LOW);
  digitalWrite(LeftMotorBackward,HIGH);
  digitalWrite(RightMotorBackward,LOW);
}

/* STOP */
void MotorStop(){
  digitalWrite(LeftMotorBackward,LOW);
  digitalWrite(RightMotorBackward,LOW);
  digitalWrite(LeftMotorForward,LOW);
  digitalWrite(RightMotorForward,LOW);
}
