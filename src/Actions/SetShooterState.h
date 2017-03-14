/*
 * SetShooterState.h
 *
 *  Created on: Mar 6, 2017
 *      Author: Brin Harper
 */

#ifndef SRC_ACTIONS_SETSHOOTERSTATE_H_
#define SRC_ACTIONS_SETSHOOTERSTATE_H_

#include "Action.h"
#include "dependency.h"
#include <vector>
#include <iostream>
#include "../plog/Log.h"

using namespace std;
class Robot;

class SetShooterState : public Action
{
    public:
        SetShooterState(int state, vector<shared_ptr<dependency>> dependencies, shared_ptr<Robot> robot);
        SetShooterState(json& action, shared_ptr<Robot> robot);

    private:
        int m_state;
        enum FlyWheels::STATE m_flywheelState;
        enum Feeder::State m_feederState;
        void run();

};




#endif /* SRC_ACTIONS_SETSHOOTERSTATE_H_ */
