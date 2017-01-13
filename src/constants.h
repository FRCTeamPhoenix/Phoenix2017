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

   //Controllers
   const static uint32_t joystick = 0;
   const static uint32_t gamepad = 1;
};

namespace DriveStationConstants{
enum butonNames{
	buttonX = 0,
	buttonA = 1,
	buttonB = 2,
	buttonY = 3,
	buttonLB = 4,
	buttonRB = 5,
	buttonLT = 6,
	buttonRT = 7,
	buttonBack = 8,
	buttoStart = 9,
	joystickLeftButton = 10,
	joystickRightButton = 11
};
}





#endif /* SRC_CONSTANTS_H_ */
