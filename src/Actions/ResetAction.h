//
// Created by William Gebhardt on 1/28/17.
//

#ifndef ACTIONGRAPHS_RESETACTION_H
#define ACTIONGRAPHS_RESETACTION_H

#include "Action.h"
#include "dependency.h"
#include <vector>
#include <iostream>

using namespace std;
using json=nlohmann::json;

class resetAction : public Action
{
public:
    resetAction(vector<int> placesToReset, vector<shared_ptr<dependency>> dependencies);

    resetAction(json& action);

    virtual void execute(vector<shared_ptr<Action>>& allActions);
private:

    vector<int> m_placesToReset;

};


#endif //ACTIONGRAPHS_RESETACTION_H
