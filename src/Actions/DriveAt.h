//
// Created by William Gebhardt on 1/31/17.
//

#ifndef PHOENIX2017_DRIVEAT_H
#define PHOENIX2017_DRIVEAT_H

#include "Action.h"
#include "dependency.h"
#include <vector>
#include <iostream>
#include "../plog/Log.h"
#include "../Robot.h"

using namespace std;

class DriveAt : public Action
{
public:
    DriveAt(double speed, double angle, vector<shared_ptr<dependency>> dependencies);

    DriveAt(json& action, shared_ptr<Robot> robot);

private:
    void run();
    void reset();

    double m_speed;
    double m_angle;
};


#endif //PHOENIX2017_DRIVEAT_H
