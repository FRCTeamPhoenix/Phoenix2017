//
// Created by William Gebhardt on 1/25/17.
//

#ifndef ACTIONGRAPHS_ACTIONGROUP_H
#define ACTIONGRAPHS_ACTIONGROUP_H

#include "Action.h"
#include "../json.hpp"
#include <fstream>

using namespace std;
using json=nlohmann::json;

class ActionGroup : public Action
{
public:
    ActionGroup(vector<shared_ptr<Action>> containedActions, vector<shared_ptr<dependency>> dependencies, vector<shared_ptr<dependency>> doneDependencies);
    ActionGroup(json& Action);
    ActionGroup();

    vector<shared_ptr<Action>>& getContainedActions()
    {
            return m_containedActions;
    };

    void resetAction(int place);

private:
    vector<shared_ptr<Action>> m_containedActions;

    vector<shared_ptr<dependency>> m_doneDependencies;
    void run();

    void reset();

    void updateCondition();
};


#endif //ACTIONGRAPHS_ACTIONGROUP_H
