//
// Created by William Gebhardt on 1/22/17.
//

#ifndef ACTIONGRAPHS_COUNTUP_H
#define ACTIONGRAPHS_COUNTUP_H

#include "Action.h"
#include "dependency.h"
#include <vector>
#include <iostream>
#include "../plog/Log.h"

using namespace std;
class CountUp : public Action
{
public:
    CountUp(int start, int end, vector<shared_ptr<dependency>> dependencies);

    CountUp(json& action);


private:
    void run();
    void reset();
    int m_start;
    int m_end;
    int m_current;
};


#endif //ACTIONGRAPHS_COUNTUP_H
