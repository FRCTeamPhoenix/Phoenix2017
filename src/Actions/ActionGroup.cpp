//
// Created by William Gebhardt on 1/25/17.
//

#include "ActionGroup.h"

ActionGroup::ActionGroup (vector<shared_ptr<Action>> containedActions, vector<shared_ptr<dependency>> dependencies, vector<shared_ptr<dependency>> doneDependencies):
    Action(dependencies),
    m_containedActions(containedActions),
    m_doneDependencies(doneDependencies)
{
}

ActionGroup::ActionGroup (json& actionGroup, shared_ptr<Robot> robot):
    Action(),
    m_containedActions(),
    m_doneDependencies()



{

    initActionGroup(actionGroup, robot);
}

ActionGroup::ActionGroup():
    Action(),
    m_containedActions(),
    m_doneDependencies()
{
}

void ActionGroup::initActionGroup (json &actionGroup, shared_ptr<Robot> robot)
{

    json containedActions = actionGroup["containedActions"];
    for(json::iterator containedAction = containedActions.begin (); containedAction != containedActions.end (); containedAction++){
        shared_ptr<Action> newAction = Action::generateAction (*containedAction, robot);
        m_containedActions.push_back (newAction);
    }

    json doneDependencies = actionGroup["doneDependencies"];
    for(json::iterator doneDependency = doneDependencies.begin (); doneDependency != doneDependencies.end (); doneDependency++){
        m_doneDependencies.push_back (make_shared<dependency>(*doneDependency));
    }

    initAction(actionGroup, robot);
}


void ActionGroup::run ()
{
//    LOGI << m_name << ":\t has run";

    vector<shared_ptr<Action>>::iterator ActionsIterator;
    for(ActionsIterator = m_containedActions.begin(); ActionsIterator != m_containedActions.end(); ActionsIterator++)
    {
        (*ActionsIterator)->execute (m_containedActions);
    }
    updateCondition ();
}

void ActionGroup::updateCondition ()
{

    bool done = false;
    vector<shared_ptr<dependency>>::iterator dependencyIterator;
    for(dependencyIterator = m_doneDependencies.begin(); dependencyIterator != m_doneDependencies.end(); dependencyIterator++)
    {
        dependency::condition dependantCondition = dependencyIterator->get ()->getCondition ();
        dependency::condition targetActionCondition = m_containedActions[dependencyIterator->get ()->getPlace ()]->getCondition ();

        if(targetActionCondition >= dependantCondition)
        {
            done = true;

        }
    }

    if(done){
        finish();
    }
    else{
        start();
    }


}

void ActionGroup::reset()
{
    resetCondition();
    vector<shared_ptr<Action>>::iterator ActionsIterator;
    for(ActionsIterator = m_containedActions.begin(); ActionsIterator != m_containedActions.end(); ActionsIterator++)
    {
        (*ActionsIterator)->reset ();
    }
}

void ActionGroup::resetAction (int place)
{
    m_containedActions[place].get ()->reset ();
}

void ActionGroup::disableAction (int place)
{
    m_containedActions[place].get ()->disable();
}
