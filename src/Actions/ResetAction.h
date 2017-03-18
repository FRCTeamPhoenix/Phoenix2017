//
// Created by William Gebhardt on 1/28/17.
//

#ifndef ACTIONGRAPHS_RESETACTION_H
#define ACTIONGRAPHS_RESETACTION_H

#include "Action.h"
#include "dependency.h"
#include <vector>
#include <iostream>
#include "../plog/Log.h"

using namespace std;
using json=nlohmann::json;

class Robot;

class resetAction : public Action
{
public:
    resetAction(vector<int> placesToReset, vector<shared_ptr<dependency>> dependencies, shared_ptr<Robot> robot);

    /*
     * Expected Json Values
     *
     * "placesToReset": array of int [recommended to include its dependencies]
     * All Base Action Json
     */
    resetAction(json& action, shared_ptr<Robot> robot);

    void execute(vector<shared_ptr<Action>>& allActions);
private:

    vector<int> m_placesToReset;

};


#endif //ACTIONGRAPHS_RESETACTION_H
