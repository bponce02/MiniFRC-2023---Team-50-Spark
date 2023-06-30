#ifndef MANIPULATOR_H
#define MANIPULATOR_H
#include <Alfredo_NoU2.h>

class Manipulator{
private:
NoU_Servo* wrist;
NoU_Servo* arm;
NoU_Motor* elevator;

int topLimitSwitchPin = 0;
int bottomLimitSwtichPin = 0;

bool elevatorPosition = false;

public:
  Manipulator(NoU_Servo* p_wrist, NoU_Servo* p_arm, NoU_Motor* p_elevator);

  void setHighRung();
  void setMiddleRung();

  void setIntakePlayerStation();
  void setIntakeGround();
};
#endif