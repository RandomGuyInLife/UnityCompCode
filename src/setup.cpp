#ifndef SETUP_H
#define SETUP_H
#include "setup.h"
#define ROTATION_PORT1
#endif

brain Brain;

controller Control = controller(primary);

motor Left1 = motor(PORT20, true);
motor Right1 = motor(PORT16, true);
motor Left2 = motor(PORT18, true);
motor Right2 = motor(PORT15, true);
motor Left3 = motor(PORT14, true);
motor Right3 = motor(PORT17, true);
motor RRight1 = motor(PORT16, false);
motor RRight2 = motor(PORT15, false);
motor RRight3 = motor(PORT17, false);
motor_group L = motor_group(Left1, Left2, Left3);
motor_group R = motor_group(RRight1, RRight2, RRight3);

drivetrain drive = drivetrain(L, R);

digital_out Piston1 = pneumatics(Brain.ThreeWirePort.A);
digital_out Piston2 = pneumatics(Brain.ThreeWirePort.B);

motor Hook = motor(PORT12);
motor Preintake = motor(PORT11);
motor bigwallstake = motor(PORT10);