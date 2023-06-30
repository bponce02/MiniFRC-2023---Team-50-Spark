#include <Alfredo_NoU2.h>
#include "SwerveModule.h"
#include "SwerveDrive.h"

SwerveDrive::SwerveDrive(NoU_Motor* p_frontLeftMotor, NoU_Motor* p_frontRightMotor, NoU_Motor* p_rearLeftMotor, NoU_Motor* p_rearRightMotor, 
      NoU_Servo* p_frontLeftServo, NoU_Servo* p_frontRightServo, NoU_Servo* p_rearLeftServo, NoU_Servo* p_rearRightServo,
      int p_frontLeftAttachedAngle, int p_frontRightAttachedAngle, int p_rearLeftAttachedAngle, int p_rearRightAttachedAngle
      ){ 
  frontLeft = new SwerveModule(p_frontLeftMotor, p_frontLeftServo, p_frontLeftAttachedAngle);
  frontRight = new SwerveModule(p_frontRightMotor, p_frontRightServo, p_frontRightAttachedAngle);
  rearLeft = new SwerveModule(p_rearLeftMotor, p_rearLeftServo, p_rearLeftAttachedAngle);
  rearRight = new SwerveModule(p_rearRightMotor, p_rearRightServo, p_rearRightAttachedAngle);
}

bool SwerveDrive::isAnglesSet(){
  if (frontLeft->isAngleSet() && frontRight->isAngleSet() && rearLeft->isAngleSet() && rearRight->isAngleSet()){
    return true;
  } else {
    return false;
  }
}

void SwerveDrive::setSpeed(float frontLeftSpeed, float frontRightSpeed, float rearLeftSpeed, float rearRightSpeed){
  if(this->isAnglesSet()){
    frontLeft->setSpeed(frontLeftSpeed);
    frontRight->setSpeed(frontRightSpeed);
    rearLeft->setSpeed(rearLeftSpeed);
    rearRight->setSpeed(rearRightSpeed);
  } else {
    frontLeft->setSpeed(0);
    frontRight->setSpeed(0);
    rearLeft->setSpeed(0);
    rearRight->setSpeed(0);
  }
}

void SwerveDrive::setAngle(float frontLeftAngle, float frontRightAngle, float rearLeftAngle, float rearRightAngle){
  frontLeft->setAngle(frontLeftAngle);
  frontRight->setAngle(frontRightAngle);
  rearLeft->setAngle(rearLeftAngle);
  rearRight->setAngle(rearRightAngle);
}

void SwerveDrive::set(float x, float y, float z){
  this->setAngle(y, y, y, y);
  this->setSpeed(x, x, x, x);
  //this->setAngle(90, 90, 90, 90);
  //this->setSpeed(x*.7, x*.7, x*.7, x*.7);
  
}
void SwerveDrive::test(int x){
  this->setAngle(1,1,1,1);
  //this->setSpeed(.8, -.8, .8, -.8);
}
