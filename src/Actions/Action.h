//
// Created by William Gebhardt on 1/22/17.
//

#ifndef ACTIONGRAPHS_ACTION_H
#define ACTIONGRAPHS_ACTION_H


#include <vector>
#include "dependency.h"
#include "../json.hpp"
#include <iostream>
#include "../plog/Log.h"
#include "../Robot.h"


using namespace std;
using json=nlohmann::json;

/** Action Overview **
 *
 * The action system is used to execute commands in both parallel and sequential order.
 * Through the use of Action Groups and Dependencies different sets of Actions will fire off
 * in specific orders when each action's Dependencies are met. This allows for multiple
 * Actions going at once but the starting and running of the Actions are interdependent
 * among other Actions in the Action Group.
 *
 *
 * Action:
 *      An object that describes an operation that the system will preform such as driving forward
 *      or waiting for a few seconds. Actions contain Dependencies that are checked every run cycle
 *      and if they are met the Action is run. Action Conditions are set when the action is run, the
 *      action is skipped over if it's condition is Finished or Disabled.
 *
 *
 * Action Groups:
 *      An organizational tool that contains Actions while being an Action itself. This allows
 *      for a group of Actions only to be called when a set of Dependencies are met and each Action
 *      inside of the group will not have to check those Dependencies. The Actions inside of the group are
 *      scoped to only be able to depend on other actions inside of the group, not up or down in the
 *      system. The groups themselves have a set of Dependencies for them being complete and this
 *      set looks at its internal actions and says the group is complete when those Done Dependencies
 *      are met.
 *
 *
 * Reset Action:
 *      This is a utility action that takes in a set of places in the group of actions it is contained with
 *      and resets them through the actions reset function.
 *
 *
 * Dependency:
 *      A dependency is a Place in a group of actions starting with 0 and a Condition. They are used when
 *      checking if the given Place's Condition is the required Condition for the dependency.
 *
 *
 * Action Factory:
 *      This is a function declaration that is the basis for how actions are loaded through a Json file.
 *      It is a part of the the base class Action. When Action Group is initialized with a Json file it
 *      uses this factory to create the actions based on a passed in Type.
 */

class Action
{
public:


    Action(vector<shared_ptr<dependency>> dependencies, shared_ptr<Robot> robot);
    Action();



    /*
     * Default:
     * Used to check if an action can be run through checking the Dependencies and if the condition of
     * the action it not Disabled or Finished
     *
     * Override:
     * Should not be overridden unless a move complex check of if the action is needed.
     */
    virtual void execute(vector<shared_ptr<Action>>& allActions);

    /*
     * Default:
     * Sets the condition of the action to NotStarted(0), will bring actions out of disabled
     *
     * Override:
     * Should be overridden to set the action back to its NotStarted condition, as well as calling
     * resetCondition
     */
    virtual void reset();

    /*
     * Used to populate the base action from the json file
     * Expected to be called in the constructor of the higher
     * level action
     *
     * Expected Json Values
     *
     * "dependencies": array of dependency objects
     * "startingCondition": int
     * "name": string
     *
     */
    void initAction(json& action, shared_ptr<Robot> robot);

    void disable();

    dependency::condition getCondition();

    string getName();

protected:

    /*
     * Default:
     * Checks if the passed in dependencies are met and if they are return true
     *
     * Override:
     * Should not be overridden unless a more complex check of dependencies is needed
     */
    virtual bool issuable(vector<shared_ptr<Action>>& allActions);

    /*
     * Default:
     * Does nothing
     *
     * Override:
     * Should be overriden and all the logic that is needed to run the action should be put in this funciton
     * as well as controlling its condition
     *
     * Note:
     * This funciton will not be called it Issuable returns false or the condition is Finished(2) or Disabled(-1)
     */
    virtual void run()
    {
        cout << "IN DEFAULT RUN" << endl;
    }

    void start(){
        m_currentCondition = dependency::Started;
    }

    void finish(){
        m_currentCondition = dependency::Finished;
    }

    void resetCondition(){
        m_currentCondition = dependency::NotStarted;
    }

    /*
     * Forward delcarationg for the actionFactory, more indepth explanation can be found in Actions/actionFactory
     */
    static shared_ptr<Action> generateAction(json& action, shared_ptr<Robot> robot);

    vector<shared_ptr<dependency>> m_dependencies;
    dependency::condition m_currentCondition;
    shared_ptr<Robot> m_robot;
    string m_name;


};


#endif //ACTIONGRAPHS_ACTION_H
