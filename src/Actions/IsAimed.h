//
// Created by William Gebhardt on 4/2/17.
//

#ifndef PHOENIX2017_ISAIMED_H
#define PHOENIX2017_ISAIMED_H


#include "Action.h"
#include "dependency.h"
#include <vector>
#include <iostream>
#include "../plog/Log.h"
#include "WPILib.h"

using namespace std;
class Robot;

class IsAimed : public Action
{
public:

    // State: 0=NoAimed, 1=Aimed
    IsAimed(vector<shared_ptr<dependency>> dependencies, shared_ptr<Robot> robot);
    IsAimed(json& action, shared_ptr<Robot> robot);

private:
    void run();
};



#endif //PHOENIX2017_ISAIMED_H
