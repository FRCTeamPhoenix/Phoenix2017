//
// Created by William Gebhardt on 1/23/17.
//

#include "Action.h"
#include <memory>
#include <fstream>



Action::Action (vector<shared_ptr<dependency>> dependencies):
    m_dependencies(dependencies),
    m_currentCondition(dependency::NotStarted)

{

}

Action::Action ():
    m_dependencies()
{

}

void Action::initAction (json &action)
{
    try
    {
        for (json::iterator d = action["dependencies"].begin (); d != action["dependencies"].end (); d++)
        {
            m_dependencies.push_back (make_shared<dependency> (*d));
        }
        m_currentCondition = (dependency::condition)(int)action["startingCondition"];
        m_name = action["name"];
    }
    catch (...)
    {
        std::cout << "dependency not passed as array" << std::endl;
        m_name = "unnamed";
    }

}

bool Action::issuable (vector<shared_ptr<Action>> &allActions)
{
    bool dependenciesMet = true;
    vector<shared_ptr<dependency>>::iterator dependencyIterator;
    for(dependencyIterator = m_dependencies.begin(); dependencyIterator != m_dependencies.end(); dependencyIterator++)
    {
        dependency::condition dependantCondition = dependencyIterator->get ()->getCondition ();
        dependency::condition targetActionCondition = allActions[dependencyIterator->get ()->getPlace ()]->getCondition ();

        if(targetActionCondition < dependantCondition)
        {
            dependenciesMet = false;
        }
    }

    return dependenciesMet;
}

dependency::condition Action::getCondition ()
{
    return m_currentCondition;
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

