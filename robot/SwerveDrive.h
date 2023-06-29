#ifndef SWERVEDRIVE_H
#define SWERVEDRIVE_H
#include <Alfredo_NoU2.h>
#include "SwerveModule.h"

class SwerveDrive{
  private:
    SwerveModule* frontLeft;
    SwerveModule* frontRight;
    SwerveModule* rearLeft;
    SwerveModule* rearRight;

    bool isAnglesSet();
    void setSpeed(float frontLeftSpeed, float frontRightSpeed, float rearLeftSpeed, float rearRightSpeed);
    void setAngle(float frontLeftAngle, float frontRightAngle, float rearLeftAngle, float rearRightAngle);
  public:
    SwerveDrive(NoU_Motor* p_frontLeftMotor, NoU_Motor* p_frontRightMotor, NoU_Motor* p_rearLeftMotor, NoU_Motor* p_rearRightMotor, 
      NoU_Servo* p_frontLeftServo, NoU_Servo* p_frontRightServo, NoU_Servo* p_rearLeftServo, NoU_Servo* p_rearRightServo,
      int p_frontLeftAttachedAngle, int p_frontRightAttachedAngle, int p_rearLeftAttachedAngle, int p_rearRightAttachedAngle
      );
    void set(float x, float y, float z);
    void test(int x);
};

#endif