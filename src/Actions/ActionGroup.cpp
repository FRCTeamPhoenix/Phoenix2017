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

ActionGroup::ActionGroup (json& actionGroup):
    Action(actionGroup)
{
    json containedActions = actionGroup["containedActions"];
    for(json::iterator containedAction = containedActions.begin (); containedAction != containedActions.end (); containedAction++){
       m_containedActions.push_back (Action::generateAction (*containedAction));
    }

    json doneDependencies = actionGroup["doneDependencies"];
    for(json::iterator doneDependency = doneDependencies.begin (); doneDependency != doneDependencies.end (); doneDependency++){
        m_doneDependencies.push_back (make_shared<dependency>(*doneDependency));
    }
}

ActionGroup::ActionGroup():
    Action()
{
        ifstream json_file;
        json_file.open("/home/lvuser/Actions.json");

        json action;
        json_file >> action;
        json_file.close ();

        json containedActions = action["containedActions"];
        for(json::iterator containedAction = containedActions.begin (); containedAction != containedActions.end (); containedAction++){
            m_containedActions.push_back (Action::generateAction (*containedAction));
        }

        json doneDependencies = action["doneDependencies"];
        for(json::iterator doneDependency = doneDependencies.begin (); doneDependency != doneDependencies.end (); doneDependency++){
            m_doneDependencies.push_back (make_shared<dependency>(*doneDependency));
        }


}

void ActionGroup::run ()
{
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
