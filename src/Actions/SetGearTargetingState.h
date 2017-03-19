//
// Created by William Gebhardt on 3/19/17.
//

#ifndef PHOENIX2017_SETGEARTARGETINGSTATE_H
#define PHOENIX2017_SETGEARTARGETINGSTATE_H

#include "Action.h"
#include "../json.hpp"
#include <fstream>
#include "../plog/Log.h"
#include "WPILib.h"

using namespace std;
using json=nlohmann::json;

class Robot;
class dependency;

class SetGearTargetingState : public Action
{
public:
    SetGearTargetingState(int state, vector<shared_ptr<dependency>> dependencies, shared_ptr<Robot> robot);

    SetGearTargetingState(json& action, shared_ptr<Robot> robot);

private:
    void run();
    void reset();

    int m_desiredState;
};


#endif //PHOENIX2017_SETGEARTARGINGSTATE_H
