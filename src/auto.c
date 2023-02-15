/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */

void spinTo(int Mnum, Encoder e, int target){
  
    float kp = .4;
  while(true){
    int counts = encoderGet(e);
    float error = target - counts;
    float output = kp * error;
    motorSet(Mnum, output);
    wait(20);
    printf("%f", error);
    printf("hehehe");
    if(error<12){
      break;
    }
    //break condition
  }
}
void autonomous() {
  //hi Mom :)
  Ultrasonic sonar;
    //sonar = ultrasonicInit(orange_port_number, yellow_port_number);
    Encoder FRencoder;
    FRencoder = encoderInit(QUAD_TOP_PORT, QUAD_BOTTOM_PORT, false);
    Encoder FLencoder;
    FLencoder = encoderInit(QUAD_TOP_PORT2, QUAD_BOTTOM_PORT2, false);
    Encoder BRencoder;
    BRencoder = encoderInit(QUAD_TOP_PORT3, QUAD_BOTTOM_PORT3, false);
    Encoder BLencoder;
    BLencoder = encoderInit(QUAD_TOP_PORT4, QUAD_BOTTOM_PORT4, false);
    encoderReset(FLencoder);
    encoderReset(FRencoder);
    encoderReset(BRencoder);
    encoderReset(BLencoder);
    spinTo(9,FRencoder,90);
    printf("done");
    wait(1000000);
}
