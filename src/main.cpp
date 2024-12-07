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

double squareSizeInches = 23;


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
  drive.driveFr(squareSizeInches * 1.5, inches);
  drive.turnFor(180, deg);
  Piston1.set(true);
  drive.turnFor(left, 95, deg);
  Hook.spinFor(-50, deg, false);
  drive.driveFor(squareSizeInches, inches);
  Hook.spinFor(forward, 270, deg, 100, velocityUnits::pct, false);
  Preintake.spinFor(2, seconds);
  drive.turnFor(left, 90, deg);
  drive.driveFor(squareSizeInches * 1.3, inches);
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
