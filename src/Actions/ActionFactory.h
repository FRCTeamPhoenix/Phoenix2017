//
// Created by William Gebhardt on 1/25/17.
//

#ifndef ACTIONGRAPHS_ACTIONFACTORY_H
#define ACTIONGRAPHS_ACTIONFACTORY_H


#include <vector>
#include <memory>
#include "../json.hpp"
#include "AllActions.h"
#include "../Robot.h"


using namespace std;
using json=nlohmann::json;

class Robot;

shared_ptr<Action> Action::generateAction (json &action, shared_ptr<Robot> robot)
{
    string type = "";
    try
    {
         type = action["type"];
    }
    catch (...)
    {
        std::cout << "No type declared" << std::endl;
        return NULL;
    }

    if ("ActionGroup" == type)
    {
        cout << "Create Action Group" << endl;

        return make_shared<ActionGroup>(action, robot);
    }
    else if("CountUp" == type)
    {
        cout << "Create Count Up" << endl;

        return make_shared<CountUp>(action, robot);
    }
    else if("resetAction" == type)
    {
        cout << "Create Reset Action" << endl;

        return make_shared<resetAction>(action, robot);
    }
    else if("GoDistance" == type)
    {
        cout << "Create Go Distance" << endl;
        shared_ptr<Action> newAction = make_shared<GoDistance>(action, robot);

        cout << "Created Go Distance" << endl;
        return newAction;
    }
    else if("Rotate" == type)
    {
        cout << "Create Rotate" << endl;
        shared_ptr<Action> newAction = make_shared<Rotate>(action, robot);
        return newAction;
    }
    else{
        cout << "Type Not Found" << endl;
        return NULL;
    }

}




#endif //ACTIONGRAPHS_ACTIONFACTORY_H
