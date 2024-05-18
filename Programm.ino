#include <AFMotor.h>

#define MOTOR_VL 4 
#define MOTOR_VR 3  
#define MOTOR_HL 1 
#define MOTOR_HR 2  

#define lineTL A0
#define lineTR A1
#define lineTM A4
 
AF_DCMotor motorVL(MOTOR_VL); 
AF_DCMotor motorVR(MOTOR_VR);
AF_DCMotor motorHL(MOTOR_HL);
AF_DCMotor motorHR(MOTOR_HR);

unsigned int norm = 110;

int valueL, valueR, valueM;  
int trigger = A2;
int echo = A3;
long duration, distance;

 
void setup() {
  Serial.begin(9600);
  pinMode(echo, INPUT);
  pinMode(trigger, OUTPUT);
     
  motorVL.run(RELEASE);  
  motorVR.run(RELEASE);
  motorHL.run(RELEASE);
  motorHR.run(RELEASE);
}
 

void loop()
{
 valueL = digitalRead(lineTL);
 valueR = digitalRead(lineTR);
 valueM = digitalRead(lineTM);

 digitalWrite(trigger, LOW);
 delayMicroseconds(2);
 digitalWrite(trigger, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigger, LOW);
 duration = pulseIn(echo,HIGH);
 distance = (duration/2)*0.03432;
 Serial.print(distance);
 Serial.println(" cm");

  if (distance > 20)
  {
    if (valueL == 0 && valueR == 1) 
    {
      motorVL.setSpeed(norm);
      motorHL.setSpeed(norm);
      
        motorVL.run(FORWARD);
        motorVR.run(RELEASE);
        motorHL.run(FORWARD);
        motorHR.run(RELEASE);
      
    }

    if (valueL == 0 && valueM == 1 && valueR == 0)
    {
      motorVL.setSpeed(norm);
      motorHL.setSpeed(norm);
      motorHL.setSpeed(norm);
      motorHR.setSpeed(norm);
        
        motorVL.run(FORWARD);
        motorVR.run(FORWARD);
        motorHL.run(FORWARD);
        motorHR.run(FORWARD);
        
    }     

    if (valueL == 1 && valueR == 0) //Rechtsdrift
    {
      motorVR.setSpeed(norm);
      motorHR.setSpeed(norm);
      
        motorVL.run(RELEASE);
        motorVR.run(FORWARD);
        motorHL.run(RELEASE);
        motorHR.run(FORWARD);
     
  	}
  }
    else
  {
    motorVL.run(RELEASE);
    motorVR.run(RELEASE);
    motorHL.run(RELEASE);
    motorHR.run(RELEASE);
  }
}

 
 


