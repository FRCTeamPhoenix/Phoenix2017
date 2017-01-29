//
// Created by William Gebhardt on 1/23/17.
//

#ifndef ACTIONGRAPHS_DEPENDENCY_H
#define ACTIONGRAPHS_DEPENDENCY_H

#include "../json.hpp"


using json=nlohmann::json;

class dependency
{
public:
    enum condition{
        Disabled = -1,
        NotStarted = 0,
        Started = 1,
        Finished = 2
    };


    dependency(int p, condition rc = Finished);

    dependency(json dependency);

    int getPlace();
    condition getCondition();


private:
    int m_place;
    condition m_requiredCondition;

};


#endif //ACTIONGRAPHS_DEPENDENCY_H
