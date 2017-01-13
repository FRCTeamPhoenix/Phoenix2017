/*
 * constants.h
 *
 *  Created on: Jan 9, 2017
 *      Author: ben
 */

#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_

struct PortAssign {
        // Channels for wheels
        const static uint32_t backLeftWheelMotor = 0;
        const static uint32_t frontLeftWheelMotor = 1;
        const static uint32_t frontRightWheelMotor = 2;
        const static uint32_t backRightWheelMotor = 3;

};


enum buttonNames
{
    buttonX = 0,
    buttonA = 1,
    buttonB = 2,
    buttonY = 3,
    buttonLB = 4,
    buttonRB = 5,
    triggerLT = 6,
    triggerRT = 7,
    buttonBack = 8,
    buttonStart = 9,
    joystickLeftButton = 10,
    joystickRightButton = 11
};


#endif /* SRC_CONSTANTS_H_ */
