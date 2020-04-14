#include <SoftwareSerial.h>


// ------ Motor Configuration --------- 
int motorA=8;   
int pwmA=9;     // Must be PWM.  In UNO these are: 3, 5, 6, 9, 10, 11
int motorB=5;
int pwmB=6;     // Must be PWM

// ------ Comms Config -------------

SoftwareSerial jeVoisSerial(10,11);
SoftwareSerial blueSerial(2,3);   // Rx, Tx

// ------ Variables ------------
int intIn = 0;
char charIn = 0;
String value = "";
int linLeft,linRight;
unsigned long last_change = millis();
int wait_time = 2000;
int maxSpeed = 126;


void setup() {
  Serial.begin(9600);
  jeVoisSerial.begin(9600);
  blueSerial.begin(9600);
  //iniMotors();
  //sendMotors(0,0);
  randomSeed(analogRead(0));
}

void loop() {

    jeVoisSerial.listen();
    while(jeVoisSerial.available()) {

      intIn = jeVoisSerial.read();
      Serial.write(intIn);
      if (intIn != '\n'){
        value += char(intIn);
      }
      else{
        Serial.println(value);
        blueSerial.println(value);
        value = "";
      }
    }
    delay(10);

    if(last_change + wait_time < millis()){
      linLeft = random(0, maxSpeed*2) - maxSpeed;
      linRight = random(0, maxSpeed*2) - maxSpeed;
      //sendMotors(linRight, linLeft);
      last_change = millis();
    }    
}

void iniMotors() {
  pinMode(motorA,OUTPUT);
  pinMode(pwmA,OUTPUT);
  pinMode(motorB,OUTPUT);
  pinMode(pwmB,OUTPUT);
}

void sendMotors(int left, int right){
  left = constrain(left,-255,255);
  right = constrain(right,-255,255);
  
  boolean bMinusLeft = left < 0;
  boolean bMinusRight = right < 0;
   
  if(bMinusLeft) {
    digitalWrite(motorA,HIGH);
    analogWrite(pwmA,255-abs(left));
  }
  else {
    digitalWrite(motorA,LOW);
    analogWrite(pwmA,abs(left));
  }
  
  if(bMinusRight) {
    digitalWrite(motorB,HIGH);
    analogWrite(pwmB,255-abs(right));
  }
  else {
    digitalWrite(motorB,LOW);
    analogWrite(pwmB,abs(right));
  }
  delay(5);
}
