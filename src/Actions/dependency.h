//
// Created by William Gebhardt on 1/23/17.
//

#ifndef ACTIONGRAPHS_DEPENDENCY_H
#define ACTIONGRAPHS_DEPENDENCY_H

#include "../json.hpp"


using json=nlohmann::json;

/*
 * dependencies store a place and a condition of another action
 */

class dependency
{
public:
    /*
     * These are the different conditions that an action can be in, to add just create a new name with the appropriate number after it.
     * Key:
     *    Failure modes : -1
     *    Waiting for commands : 0
     *    Running modes : 1
     *    Finished modes : 2
     *
     */
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
