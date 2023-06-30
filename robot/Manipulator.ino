#include <Alfredo_NoU2.h>
#include "Manipulator.h"

Manipulator::Manipulator(NoU_Servo* p_wrist, NoU_Servo* p_arm, NoU_Motor* p_elevator){
  pinMode(this->bottomLimitSwtichPin, INPUT);
  pinMode(this->topLimitSwitchPin, INPUT);
}
void Manipulator::setHighRung(){

}

void Manipulator::setMiddleRung(){

}

void Manipulator::setIntakePlayerStation(){

}

void Manipulator::setIntakeGround(){

}