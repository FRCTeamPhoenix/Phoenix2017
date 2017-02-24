//
// Created by William Gebhardt on 2/18/17.
//

#ifndef PHOENIX2017_INDEXERRUNTIME_H
#define PHOENIX2017_INDEXERRUNTIME_H

#include "Action.h"
#include "dependency.h"
#include <vector>
#include <iostream>
#include "../plog/Log.h"
#include "../Robot.h"

using namespace std;

class IndexerRunTime : public Action
{
    IndexerRunTime(double speed, double duration, vector<shared_ptr<dependency>> dependencies, shared_ptr<Robot> robot);

    IndexerRunTime(json& action, shared_ptr<Robot> robot);

private:
    void run();
    void reset();

    double m_speed;
    double m_duration;

    Timer m_timer;
};


#endif //PHOENIX2017_INDEXERRUNTIME_H