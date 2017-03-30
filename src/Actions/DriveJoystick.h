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

using namespace std;

class Robot;

class DriveJoystick: public Action {
public:
	DriveJoystick(vector<shared_ptr<dependency>> dependencies, shared_ptr<Robot> robot);
	DriveJoystick(json& action, shared_ptr<Robot> robot);
    virtual ~DriveJoystick();



private:
	void run();
	void reset();

};

#endif /* SRC_ACTIONS_DRIVEJOYSTICK_H_ */
