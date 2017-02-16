/*
 * DriveJoysitck.h
 *
 *  Created on: Feb 15, 2017
 *      Author: larry
 */

#ifndef SRC_ACTIONS_DRIVEJOYSTICK_H_
#define SRC_ACTIONS_DRIVEJOYSTICK_H_

#include "Action.h"
#include "dependency.h"
#include <vector>
#include <iostream>
#include "../plog/Log.h"
#include "../Robot.h"

using namespace std;

class DriveJoystick: public Action {
public:
	DriveJoystick(vector<shared_ptr<dependency>> dependencies);
	DriveJoystick(json& action, shared_ptr<Robot> robot);

private:
	void run();
	void reset();
	virtual ~DriveJoystick();
};

#endif /* SRC_ACTIONS_DRIVEJOYSTICK_H_ */
