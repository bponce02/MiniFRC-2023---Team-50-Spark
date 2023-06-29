2#include <Alfredo_NoU2.h>
#include "SwerveModule.h"
#include <cmath>

//the subtraction/addition of 90 accounts for the servo's range of motion in the swerve module.
SwerveModule::SwerveModule(NoU_Motor* p_motor, NoU_Servo* p_servo, int p_attachedAngle){
  motor = p_motor;
  servo = p_servo; 
  minPosition = this->convertToDegrees(p_attachedAngle -  90);
  maxPosition = this->convertToDegrees(p_attachedAngle + 90);
  attachedAngle = p_attachedAngle;
}

int SwerveModule::convertToDegrees(int degrees){
  int convertedDegrees = degrees % 360;
  if(convertedDegrees < 0){
    convertedDegrees += 360;
  }
  return convertedDegrees;
}

bool SwerveModule::compareServoDegreesToDegrees(int degrees){
  if(minPosition < maxPosition){
    return std::round(servo->getDegrees()) == this->degreesToServoDegrees(this->convertToDegrees(degrees + maxPosition));
  } else {
    return std::round(servo->getDegrees()) == this->degreesToServoDegrees(this->convertToDegrees(degrees - minPosition));
  }
}

void SwerveModule::reverseMotors(int degrees){
  /*
  if(180 < this->attachedAngle){
    if(!(this->convertToDegrees(degrees - (maxPosition + 45)) > 180  || 180 > this->convertToDegrees(degrees - minPosition - 45))){
      reverseMotor = true;
    } else {
      reverseMotor = false;
    }
  } else {
    if(this->convertToDegrees(degrees - (maxPosition - 45)) > 180  || 180 > this->convertToDegrees(degrees + minPosition + 45)){
      reverseMotor = true;
    } else {
      reverseMotor = false;
    }
  }
  */
  float radians = ((degrees - 45) * (3.14/180));
  if(0 < this->attachedAngle < 90 || 180 < this->attachedAngle < 270){
    if (std::sin(radians) > 0){
      reverseMotor = true;
    } else {
       reverseMotor = false;
    }
  } else {
    if (std::cos(radians) > 0){
      reverseMotor = false;
    } else {
       reverseMotor = true;
    }
  }
  //if(180 > this->attachedAngle){
   // reverseMotor = !reverseMotor;
  //}
}

int SwerveModule::degreesToServoDegrees(int degrees){
  //Serial.print("reverse Motor: ");
  //Serial.print(reverseMotor);
  //Serial.print("degrees: ");
  //Serial.print(degrees);
  //Serial.print("servo degrees: ");
  int servoDegrees = degrees % 180;
  //Serial.println(servoDegrees);
  //Serial.print("degrees");
  //Serial.println(degrees);
  
  this->reverseMotors(degrees);
 
  //if(degrees - maxPosition > (degrees - maxPosition) % 180){
  //if(degrees > this->convertToDegrees(degrees - maxPosition)){
  //if(degrees > this->convertToDegrees(180 - minPosition)){
   /* 
  //if(this->convertToDegrees(degrees - (maxPosition - 45)) > 180  || 180 > this->convertToDegrees(degrees - minPosition + 45)){
    if(!(this->convertToDegrees(degrees - (maxPosition + 45)) > 180  || 180 > this->convertToDegrees(degrees - minPosition - 45))){
  //if(compareServoDegreesToDegrees(degrees)){
    reverseMotor = true;
    //reverseMotor = fale;
  } else {
    reverseMotor = false;
  }
  */
  
  if(servoDegrees < 0){
    return servoDegrees += 180;
  } else {
    return servoDegrees;
  }
}

bool SwerveModule::isAngleSet() {
  return angleSet;
}

void SwerveModule::setAngle(int degrees){
  currentMillis = millis();
  if(!this->compareServoDegreesToDegrees(degrees)){
    previousMillis = millis();
    if(minPosition < maxPosition){
      servo->write(this->degreesToServoDegrees(this->convertToDegrees(degrees + maxPosition)));
    } else {
      servo->write(this->degreesToServoDegrees(this->convertToDegrees(degrees - minPosition)));
    }
    angleSet = false;
  } else if (currentMillis - previousMillis >= interval){
    angleSet = true;
  } else {
    angleSet = false;
  }
}

void SwerveModule::setSpeed(float speed){
  if (angleSet){
    if (reverseMotor == false){
      motor->set(speed);
    } else {
      motor->set(speed * -1);
    }
  }
}