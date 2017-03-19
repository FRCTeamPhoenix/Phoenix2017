/*
 * SetShooterState.h
 *
 *  Created on: Mar 6, 2017
 *      Author: Brin Harper
 */

#ifndef SRC_ACTIONS_SETSHOOTERSTATE_H_
#define SRC_ACTIONS_SETSHOOTERSTATE_H_

#include "Action.h"
#include "FlyWheels.h"
#include "Feeder.h"
#include "dependency.h"
#include <vector>
#include <iostream>
#include "../plog/Log.h"

using namespace std;
class Robot;

class SetShooterState : public Action
{
    public:

        // State: 0=OFF, 1=FLATRATE, 2=LIDARRATE, 3=JOYSTICKRATE
        // State numbers have been chosen to match class enums
        SetShooterState(int state, vector<shared_ptr<dependency>> dependencies, shared_ptr<Robot> robot);
        SetShooterState(json& action, shared_ptr<Robot> robot);

    private:
        int m_state;
        void run();

};




#endif /* SRC_ACTIONS_SETSHOOTERSTATE_H_ */
