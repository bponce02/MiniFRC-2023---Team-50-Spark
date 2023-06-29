#ifndef SWERVEMODULE_H
#define SWERVEMODULE_H
#include <Alfredo_NoU2.h>
#include <cmath>

class SwerveModule{
private:
  NoU_Motor* motor;
  NoU_Servo* servo;

  bool angleSet = true;

  unsigned long previousMillis = 0; 
  unsigned long currentMillis;
  unsigned long interval = 250;

  int degrees = 0;
  int minPosition;
  int maxPosition;
  bool reverseMotor = false;
  int attachedAngle;

  int convertToDegrees(int degrees);
  int degreesToServoDegrees(int degrees);
  bool compareServoDegreesToDegrees(int degrees);
  void reverseMotors(int degrees);

public:
  SwerveModule(NoU_Motor* p_motor, NoU_Servo* p_servo, int p_attachedAngle);
  void setAngle(int degrees);
  void setSpeed(float speed);
  bool isAngleSet();
};

#endif