/**
 * Example code for a robot using an ESP32 and NoU2 controlled with the keyboard from AlfredoConnect.
 * The NoU2 library can be found at https://github.com/AlfredoElectronics/Alfredo-NoU2.
 *
 * Detailed instructions can be found at https://github.com/AlfredoElectronics/AlfredoConnect-Receive/.
 */

#include <AlfredoConnect.h>
#include <BluetoothSerial.h>
#include <Alfredo_NoU2.h>
#include "SwerveDrive.h"
#include <cmath>

BluetoothSerial bluetooth;

// If your robot has more than a drivetrain and one servo, add those actuators here 
NoU_Motor frontLeftMotor(6);
NoU_Motor frontRightMotor(5);
NoU_Motor rearLeftMotor(1);
NoU_Motor rearRightMotor(4); 

NoU_Servo frontLeftServo(1);
NoU_Servo frontRightServo(2);
NoU_Servo rearLeftServo(4);
NoU_Servo rearRightServo(3);

// This creates the drivetrain object, you shouldn't have to mess with this
SwerveDrive drivetrain(&frontLeftMotor, &frontRightMotor, &rearLeftMotor, &rearRightMotor,
  &frontLeftServo, &frontRightServo, &rearLeftServo, &rearRightServo,315,45,225,135);

float deadband(float value, float deadband){
  if(std::abs(value) < deadband){
    return 0;
  }
  return value;
}
void setup() {
  Serial.begin(9600);
//EVERYONE SHOULD CHANGE "ESP32 Bluetooth" TO THE NAME OF THEIR ROBOT HERE BEFORE PAIRING THEIR ROBOT TO ANY LAPTOP
    bluetooth.begin("Team 50 - Spark");
    AlfredoConnect.begin(bluetooth);
    bluetooth.println("ArcadeBotGamepad started");

// If a motor in your drivetrain is spinning the wrong way, change the value for it here from 'false' to 'true'
  frontLeftMotor.setInverted(true);
  frontRightMotor.setInverted(false);
  rearLeftMotor.setInverted(true);
  rearRightMotor.setInverted(false);

// No need to mess with this code

    RSL::initialize();
    RSL::setState(RSL_ENABLED);
}

void loop() {
  Serial.println("I PREVENT BROWNOUTS DONT REMOVE ME");
// Here we define the variables we use in the loop
    double throttle = 0;
    int rotation = 0;
    int servoAngle = 0;

// Here we decide what the throttle and rotation direction will be based on what key is pressed 
    if (AlfredoConnect.getGamepadCount() >= 1) {
        float throttle = -AlfredoConnect.getAxis(0, 1);
        float rotation = AlfredoConnect.getAxis(0, 0);

        float pi = 3.14;
        float angle = std::atan2(deadband(AlfredoConnect.getAxis(0, 0),.1) * pi / 180, -deadband(AlfredoConnect.getAxis(0, 1),.1) * pi / 180);
        float speed = deadband(-std::hypot(AlfredoConnect.getAxis(0, 1) * pi / 180, AlfredoConnect.getAxis(0, 0) * pi / 180),0);

        drivetrain.set(speed * (180 / pi), (angle * (180 / pi)),0);

        RSL::setState(RSL_ENABLED);
    } else {
        RSL::setState(RSL_DISABLED);
    }

// Here we decide what the servo angle will be based on if the Q key is pressed ()
    if (AlfredoConnect.keyHeld(Key::Q)) {
      Serial.println("KILL ME");
        servoAngle = 50;
    }
    else {
        servoAngle = 110;
    }

// No need to mess with this code
    AlfredoConnect.update();
    RSL::update();
}

