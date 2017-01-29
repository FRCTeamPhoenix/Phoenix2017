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


shared_ptr<Action> Action::generateAction (json &action)
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
        return make_shared<ActionGroup>(action);
    }
    else if("CountUp" == type)
    {
        return make_shared<CountUp>(action);
    }
    else if("resetAction" == type)
    {
        return make_shared<resetAction>(action);
    }
    else{
        cout << "Type Not Found" << endl;
        return NULL;
    }

}




#endif //ACTIONGRAPHS_ACTIONFACTORY_H
