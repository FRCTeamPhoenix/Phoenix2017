//
// Created by William Gebhardt on 3/30/17.
//

#ifndef PHOENIX2017_SETTURRETSTATE_H
#define PHOENIX2017_SETTURRETSTATE_H

#include "Action.h"
#include "dependency.h"
#include <vector>
#include <iostream>
#include "../plog/Log.h"
#include "WPILib.h"

using namespace std;
class Robot;

class SetTurretState : public Action
{
    public:
        SetTurretState(int state, vector<shared_ptr<dependency>> dependencies, shared_ptr<Robot> robot);
        SetTurretState(json& action, shared_ptr<Robot> robot);

    private:
        int m_state;
        void run();
        void reset();

};


#endif //PHOENIX2017_SETTURRETSTATE_H
