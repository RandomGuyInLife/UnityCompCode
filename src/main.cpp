/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Alex OR, Kiernan S.                                       */
/*    Created:      9/19/2024, 3:23:36 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#ifndef SETUP_H
#define SETUP_H
#include "setup.h"
#include <string>
#endif

using namespace vex;

// A global instance of competition
competition Competition;

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void pressedPnueDown(void){
  Piston1.set(false);
 
}

void pressedPnueUp(void){
  Piston1.set(true);

}

void DBDown(void) {
  Piston2.set(true);
}

void DBUp(void) {
  Piston2.set(false);
}

void autonomous(void) {
  // ..........................................................................
  Hook.spinFor(reverse, 1, seconds, 50, vex::velocityUnits::pct);
  drive.driveFor(36, inches);
  drive.driveFor(1, inches, false);
  Preintake.spinFor(180, deg, false);
  Hook.spinFor(forward, 2, seconds, 50, vex::velocityUnits::pct);
  drive.turnFor(-45, degrees);
  drive.driveFor(-12, inches);
  drive.turnFor(90, degrees);
  drive.driveFor(12, inches);
  drive.turnFor(-90, degrees);
  drive.driveFor(-6, inches);
  Hook.spinFor(forward, 2, seconds, 100, vex::velocityUnits::pct);
  // ..........................................................................
}

void usercontrol(void) {
  Control.ButtonL1.pressed(pressedPnueDown);
  Control.ButtonL2.pressed(pressedPnueUp);
  //Control.ButtonX.pressed(DBDown);
  //Control.ButtonX.pressed(DBUp);
  Brain.Screen.setPenColor(0xFF0000);
  // User control code here, inside the loop
  while (1) {
    int LeftPower = Control.Axis3.position(pct) + Control.Axis1.position(pct); // Port 3 first (-)
    int RightPower = Control.Axis3.position(pct) - Control.Axis1.position(pct); // Port 3 first (+)
    Left1.spin(forward, LeftPower, pct);
    Right1.spin(forward, RightPower, pct);
    Left2.spin(forward, LeftPower, pct);
    Right2.spin(forward, RightPower, pct);
    Left3.spin(forward, LeftPower, pct);
    Right3.spin(forward, RightPower, pct);
    
    if (Control.ButtonR1.pressing()){
      Preintake.spin(forward, 100, pct);
      Hook.spin(forward, 100, pct);
    } else if (Control.ButtonR2.pressing()) {
      Preintake.spin(reverse, 100, pct);
      Hook.spin(reverse, 100, pct);
    } else{
      Preintake.spin(forward, 0, pct);
      Hook.spin(reverse, 0, pct);
    }

    if (Control.ButtonUp.pressing()){
      bigwallstake.spin(forward, 100, pct);
    } else if (Control.ButtonDown.pressing()) {
      bigwallstake.spin(reverse, 100, pct);
    } else {
      bigwallstake.spin(forward, 0, pct);
    }
    

  }
  
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);

  }
}
