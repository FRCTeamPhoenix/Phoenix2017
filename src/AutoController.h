#pragma once

#include "Actions/Actions.h"
#include "CommandParser.h"
#include <queue>

class AutoController
{
public:
    AutoController(void);
    virtual ~AutoController(void);

    void run(void);
    bool performAction(void);
    void clearQueue(void);
    void pushAction(Action*);
private:
    CommandParser m_parser;
    std::queue<Action*> m_queue;
};
