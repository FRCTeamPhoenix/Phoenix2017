//
// Created by William Gebhardt on 2/5/17.
//

#ifndef PHOENIX2017_ROTATE_H
#define PHOENIX2017_ROTATE_H

#include "Action.h"
#include "../json.hpp"
#include <fstream>
#include "../plog/Log.h"
#include "../Robot.h"


using namespace std;
using json=nlohmann::json;

class Rotate : public Action
{
public:
    Rotate(double angle, double speed, double tolerance, vector<shared_ptr<dependency>> dependencies, shared_ptr<Robot> robot);

    Rotate(json& action, shared_ptr<Robot> robot);

private:
    void run();
    void reset();

    Timer m_timer;
    double m_angle;
    double m_speed;
    double m_tolerance;
};


#endif //PHOENIX2017_ROTATE_H
