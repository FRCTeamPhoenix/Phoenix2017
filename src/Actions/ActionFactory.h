//
// Created by William Gebhardt on 1/25/17.
//

#ifndef ACTIONGRAPHS_ACTIONFACTORY_H
#define ACTIONGRAPHS_ACTIONFACTORY_H


#include <vector>
#include <memory>
#include "../json.hpp"
#include "AllActions.h"

using namespace std;
using json=nlohmann::json;

class Robot;

/*
 * This is where the actions are created in the heep and then pushed to an action group.
 * All the actions that come out of this factory need to be created through their Json
 * constructor. When a new action type is created it needs to be added to the factory,
 * if the type of an action can not be determained or is not found an empty action is returned.
 *
 * Expected Json Values
 *
 * "type": one of the types below as a string
 * All expected Json values for the desired action and for a base action
 */

shared_ptr<Action> Action::generateAction (json &action, json& allActionsJson, shared_ptr<Robot> robot)
{
    string type = "";
    try
    {
         type = action["type"];
    }
    catch (...)
    {
        std::cout << "No type declared" << std::endl;
        return make_shared<Action>();
    }

    if ("ActionGroup" == type)
    {
        return make_shared<ActionGroup>(action, allActionsJson, robot);
    }
    else if("CountUp" == type)
    {
        return make_shared<CountUp>(action, robot);
    }
    else if("resetAction" == type)
    {
        return make_shared<resetAction>(action, robot);
    }
    else if("GoDistance" == type)
    {
        return make_shared<GoDistance>(action, robot);
    }
    else if("Rotate" == type)
    {
        return make_shared<Rotate>(action, robot);
    }
    else if("DriveJoystick" == type)
    {
        return make_shared<DriveJoystick>(action, robot);
    }
    else if("IndexerRunTime" == type)
    {
        return make_shared<IndexerRunTime>(action, robot);
    }
    else if("SetIndexerState" == type)
    {
        return make_shared<SetIndexerState>(action, robot);
    }
    else if("SetShooterState" == type)
    {
        return make_shared<SetShooterState>(action, robot);
    }
    else if("SetTurretState" == type)
    {
        return make_shared<SetTurretState>(action, robot);
    }
    else if("IsAimed" == type)
    {
        return make_shared<IsAimed>(action, robot);
    }
    else if("CommonActionRef" == type)
    {
    	json& commonActions = allActionsJson["Common_Actions"];
        string commonAction = action["commonAction"];

        json commonActionJson = commonActions[commonAction];

        commonActionJson["dependencies"] = action["dependencies"];
        cout << "Common Action Fonud" << endl;
        return generateAction(commonActionJson, allActionsJson, robot);

    }
    else{
        cout << "Type Not Found" << endl;
        return NULL;
    }

}




#endif //ACTIONGRAPHS_ACTIONFACTORY_H
