//
// Created by William Gebhardt on 1/23/17.
//

#include "Action.h"
#include <memory>
#include <fstream>



Action::Action (vector<shared_ptr<dependency>> dependencies):
    m_dependencies(dependencies),
    m_currentCondition(dependency::NotStarted),
    m_robot(NULL)

{

}

Action::Action ():
    m_dependencies(),
    m_currentCondition(dependency::NotStarted),
    m_robot(NULL)
{

}


void Action::initAction (json &action, shared_ptr<Robot> robot)
{

    m_name = "unnamed";
    m_robot = robot;

    json deps = action["dependencies"];

    for (json::iterator d = deps.begin (); d != deps.end (); d++)
    {
        m_dependencies.push_back (make_shared<dependency> (*d));
    }
    m_currentCondition = (dependency::condition)action["startingCondition"].get<int>();
    m_name = action["name"];

}

bool Action::issuable (vector<shared_ptr<Action>> &allActions)
{
    bool dependenciesMet = true;
    vector<shared_ptr<dependency>>::iterator dependencyIterator;
    for(dependencyIterator = m_dependencies.begin(); dependencyIterator != m_dependencies.end(); dependencyIterator++)
    {
        dependency::condition dependantCondition = dependencyIterator->get ()->getCondition ();
        dependency::condition targetActionCondition = allActions[dependencyIterator->get ()->getPlace ()]->getCondition ();

        if(targetActionCondition != dependantCondition)
        {
            dependenciesMet = false;
        }
    }

    return dependenciesMet;
}

void Action::execute (vector<shared_ptr<Action>>& allActions)
{
    if(dependency::condition::Disabled == getCondition()){
        return;
    }

    if(dependency::condition::Finished == getCondition())
    {
        return;
    }


    if(issuable (allActions))
    {
        run();
    }


}

void Action::reset()
{
    cout << "IN DEFAULT RESET" << endl;
    resetCondition();
}


dependency::condition Action::getCondition ()
{
    return m_currentCondition;
}

void Action::disable()
{
    m_currentCondition = dependency::Disabled;
}

string Action::getName ()
{
    return m_name;
}