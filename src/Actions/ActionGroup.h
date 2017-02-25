//
// Created by William Gebhardt on 1/25/17.
//

#ifndef ACTIONGRAPHS_ACTIONGROUP_H
#define ACTIONGRAPHS_ACTIONGROUP_H
#include "Action.h"
#include "../json.hpp"
#include <fstream>
#include "../plog/Log.h"
#include "../Robot.h"



using namespace std;
using json=nlohmann::json;

/* Action Groups:
 *      An organizational tool that contains Actions while being an Action itself. This allows
 *      for a group of Actions only to be called when a set of Dependencies are met and each Action
 *      inside of the group will not have to check those Dependencies. The Actions inside of the group are
 *      scoped to only be able to depend on other actions inside of the group, not up or down in the
 *      system. The groups themselves have a set of Dependencies for them being complete and this
 *      set looks at its internal actions and says the group is complete when those Done Dependencies
 *      are met.
 */

class ActionGroup : public Action
{
public:
    ActionGroup(vector<shared_ptr<Action>> containedActions, vector<shared_ptr<dependency>> dependencies, vector<shared_ptr<dependency>> doneDependencies, shared_ptr<Robot> robot);
    ActionGroup(json& actionGroup, shared_ptr<Robot> robot);
    ActionGroup();

    vector<shared_ptr<Action>>& getContainedActions()
    {
            return m_containedActions;
    };

    /*
     * Usage:
     * Used to create a top level action group, pair with empty constructor intended for
     * member action groups
     *
     * Expected Json Values
     *
     * "containedActions": an array of other actions [min 1]
     * "doneDependencies": an array of dependency objects [leave empty to run forever]
     * All Base Action Json
     *
     */
    void initActionGroup(json& actionGroup, shared_ptr<Robot> robot);

    /*
     * Reset and Disable an action inside of the contained actions
     */
    void resetAction(int place);
    void disableAction(int place);


private:


    vector<shared_ptr<Action>> m_containedActions;

    vector<shared_ptr<dependency>> m_doneDependencies;

    /*
     * Calls the execute on all actions inside of the contained actions
     */
    void run();

    /*
     * Calls the reset on all actions inside of the contained actions
     */
    void reset();

    /*
     * Checks if the doneDependencies are met if they are sets the group to finished
     */
    void updateCondition();
};


#endif //ACTIONGRAPHS_ACTIONGROUP_H
