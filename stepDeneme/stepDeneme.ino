#include <Stepper.h>
const int stepsPerRev = 100;
const int stepSpeed = 20; //set the speed at 60 rpm 
Stepper motor(stepsPerRev, 8, 9, 10, 11);

void setup() {
  // put your setup code here, to run once:
  motor.setSpeed(stepSpeed);// Set the motor speed in rotations per minute(RPMs)

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("cw\n");
  motor.step(stepsPerRev); // step one revolution in one direction
  delay(500);

  Serial.print("ccw\n");
  motor.step(-stepsPerRev);
  delay(500);
}
