//
// Created by William Gebhardt on 2/2/17.
//

#ifndef PHOENIX2017_GODISTANCE_H
#define PHOENIX2017_GODISTANCE_H

#include "Action.h"
#include "../json.hpp"
#include <fstream>
#include "../plog/Log.h"
#include "WPILib.h"

using namespace std;
using json=nlohmann::json;

class Robot;

class GoDistance : public Action
{
public:
    GoDistance(double distance, double angle, double speed, double tolerance, vector<shared_ptr<dependency>> dependencies, shared_ptr<Robot> robot);

    GoDistance(json& action, shared_ptr<Robot> robot);

private:
    void run();
    void reset();

    frc::Timer m_timer;
    double m_distance;
    double m_angle;
    double m_speed;
    double m_tolerance;


};


#endif //PHOENIX2017_GODISTANCE_H
