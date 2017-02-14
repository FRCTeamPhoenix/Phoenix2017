//
// Created by William Gebhardt on 1/28/17.
//

#include "ResetAction.h"


resetAction::resetAction (vector<int> placeToReset, vector<shared_ptr<dependency>> dependencies):
    Action(dependencies),
    m_placesToReset(placeToReset)
{ }

resetAction::resetAction (json &action, shared_ptr<Robot> robot):
    Action()
{
    for (json::iterator it = action["placesToReset"].begin (); it != action["placesToReset"].end (); it++)
    {
        m_placesToReset.push_back (*it);
    }

    initAction(action, robot);

}


void resetAction::execute (vector<shared_ptr<Action>> &allActions)
{

    if(issuable(allActions)){
        LOGI << m_name << ":\t has reset actions";

        disable();

        for (vector<int>::iterator it = m_placesToReset.begin(); it != m_placesToReset.end(); it++)
        {
            allActions[*it].get ()->reset ();


        }
    }

}




