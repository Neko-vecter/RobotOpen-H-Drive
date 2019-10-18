#include <SPI.h>
#include <Ethernet.h>
#include <EEPROM.h>
#include <Servo.h>
#include <RobotOpenHA.h>

/* I/O Setup */
ROJoystick usb1(1);         // Joystick #1

ROPWM leftDrive(5);
ROPWM rightDrive(6);
ROPWM H_Drive(3);

int W_Light = 53;

void setup()
{
  /* Initiate comms */
  RobotOpen.begin(&enabled, &disabled, &timedtasks);
  /* Set IPAddress Subnet Gateway */
  /* You can change IPAddress in the library "RobotOpenHA.cpp" */
  //RobotOpen.setIP(IPAddress(192, 168, 1, 23));
  //RobotOpen.setSubnet(IPAddress(255,255,255,0));
  //RobotOpen.setGateway(IPAddress(192, 168, 1, 1));

  leftDrive.attach();
  rightDrive.attach();
  H_Drive.attach();

  //pinMode(W_Light, OUTPUT);

}


/* This is your primary robot loop - all of your code
   should live here that allows the robot to operate
*/
void enabled() {
  //The code for Joy??
  int FBPower = constrain((usb1.leftY()), 0, 255);

  int leftPower = constrain((usb1.rightX()), 0, 255);
  int rightPower = constrain((usb1.rightX()), 0, 255);

  int H_Power = constrain ((usb1.leftX()), 0, 255);

  leftDrive.write(127-FBPower+leftPower);
  rightDrive.write(127+FBPower-rightPower);
  H_Drive.write(H_Power);

  //The code for light?? 
  
}


/* This is called while the robot is disabled */
void disabled() {
  // safety code!!

  // safety code for light
  digitalWrite(W_Light, HIGH);

  // neutral out PWMs
  leftDrive.write(0);
  rightDrive.write(0);
  H_Drive.write(0);
}


/* This loop ALWAYS runs - only place code here that can run during a disabled state
   This is also a good spot to put driver station publish code
*/
void timedtasks() {
  RODashboard.publish("Uptime Seconds", ROStatus.uptimeSeconds());
}


// !!! DO NOT MODIFY !!!
void loop() {
  RobotOpen.syncDS();
}
