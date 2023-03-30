#include <Stepper.h>

#define stepsPerRotation 1600

Stepper stepperTop = Stepper(stepsPerRotation, 3,4);
Stepper stepperBottom = Stepper(stepsPerRotation, 5,6);
Stepper stepperLeft = Stepper(stepsPerRotation, 7,8);
Stepper stepperRight = Stepper(stepsPerRotation, 9,10);
Stepper stepperBack = Stepper(stepsPerRotation, 12,13);

const int turnRight = 1600;
const int turnLeft = 4800;
const int turnHalve = 3200;

void setup() {
  // put your setup code here, to run once:
  stepperTop.setSpeed(240);
  stepperBottom.setSpeed(240);
  stepperLeft.setSpeed(240);
  stepperRight.setSpeed(240);
  stepperBack.setSpeed(240);
  //  scrambleCube();
  for (int i = 0; i < 4; ++i){
    stepperRight.step(turnRight);
     stepperLeft.step(turnRight);
     stepperBottom.step(turnHalve);
     stepperTop.step(turnHalve);
     stepperRight.step(turnLeft);
     stepperLeft.step(turnLeft);
     stepperBack.step(turnRight);
     stepperRight.step(turnRight);
     stepperLeft.step(turnRight);
     stepperBottom.step(turnHalve);
     stepperTop.step(turnHalve);
     stepperRight.step(turnLeft);
     stepperLeft.step(turnLeft);
    delay(1000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}


void scrambleCube(){
  while (true){
    long seed = analogRead(A0);
    if (seed != 0){
      randomSeed(seed);
      break;
    }
  }
  
  for (int i = 0; i <17; ++i){
    int r = random(12);
    switch(r){
      case 0:
       stepperRight.step(turnRight);
       stepperLeft.step(turnRight);
       stepperBottom.step(turnHalve);
       stepperTop.step(turnHalve);
       stepperRight.step(turnLeft);
       stepperLeft.step(turnLeft);
       stepperBack.step(turnRight);
       stepperRight.step(turnRight);
       stepperLeft.step(turnRight);
       stepperBottom.step(turnHalve);
       stepperTop.step(turnHalve);
       stepperRight.step(turnLeft);
       stepperLeft.step(turnLeft);
      case 1:
       stepperRight.step(turnRight);
       stepperLeft.step(turnRight);
       stepperBottom.step(turnHalve);
       stepperTop.step(turnHalve);
       stepperRight.step(turnLeft);
       stepperLeft.step(turnLeft);
       stepperBack.step(turnLeft);
       stepperRight.step(turnRight);
       stepperLeft.step(turnRight);
       stepperBottom.step(turnHalve);
       stepperTop.step(turnHalve);
       stepperRight.step(turnLeft);
       stepperLeft.step(turnLeft);
      case 2:
        stepperRight.step(turnRight);
      case 3: 
        stepperRight.step(turnLeft);
      case 4:
        stepperLeft.step(turnRight);
      case 5:
        stepperLeft.step(turnLeft);
      case 6:
        stepperBack.step(turnRight);
      case 7:
        stepperBack.step(turnLeft);
      case 8:
        stepperTop.step(turnRight);
      case 9:
        stepperTop.step(turnLeft);
      case 10:
        stepperBottom.step(turnRight);
      case 11:
        stepperBottom.step(turnLeft);
    }
  }
  delay(100);
}
