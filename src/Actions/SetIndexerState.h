/*
 * SetIndexerState.h
 *
 *  Created on: Mar 6, 2017
 *      Author: Brin Harper
 */

#ifndef SRC_ACTIONS_SETINDEXERSTATE_H_
#define SRC_ACTIONS_SETINDEXERSTATE_H_

#include "Action.h"
#include "dependency.h"
#include <vector>
#include <iostream>
#include "../plog/Log.h"

using namespace std;
class Robot;

class SetIndexerState : public Action
{
    public:
        SetIndexerState(enum Indexer::State state, vector<shared_ptr<dependency>> dependencies, shared_ptr<Robot> robot);
        SetIndexerState(json& action, shared_ptr<Robot> robot);

    private:
        enum Indexer::State m_state;
        void run();

};



#endif /* SRC_ACTIONS_SETINDEXERSTATE_H_ */
