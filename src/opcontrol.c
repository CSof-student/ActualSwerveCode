/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */

void closeLoopControl(int Mnum, int target, Encoder e)
{
    int counts = encoderGet(e);
    float kp = .4;
    float error = target - counts;
    float output = kp * error;
    motorSet(Mnum, output);
    wait(20);
    printf("output: %f \n", output);
    printf("counts: %d \n", counts);
}

void operatorControl()
{
    // encoderReset(FRencoder);
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
    while (true)
    {
        /*print("Hello from SB and me2 oh yeah ththatis\n");
        //std::cout << "hello world" << std::endl;

       //while(joystickGetAnalog(1,1) != 0){
         if(encoderGet(FRencoder) > 200||encoderGet(FRencoder) < -200){
            //motorSet(9,20);
            print("hi");
         }
         else{
            print ("bye");
         }
             wait(2000);

        //}


    }*/
        closeLoopControl(9, atan2(joystickGetAnalog(1, 2), joystickGetAnalog(1, 1)) * (180 / 3.1415), FRencoder);
        closeLoopControl(7, atan2(joystickGetAnalog(1, 2), joystickGetAnalog(1, 1)) * (180 / 3.1415), FLencoder);
        closeLoopControl(8, atan2(joystickGetAnalog(1, 2), joystickGetAnalog(1, 1)) * (180 / 3.1415), BRencoder);
        closeLoopControl(6, atan2(joystickGetAnalog(1, 2), joystickGetAnalog(1, 1)) * (180 / 3.1415), BLencoder);

        float val = atan2(joystickGetAnalog(1, 2), joystickGetAnalog(1, 1)) * (180 / 3.1415);
        printf("joystick val: %f \n", val);
        wait(20);
    }
}