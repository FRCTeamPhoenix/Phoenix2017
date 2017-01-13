#pragma once

#include "Actions.h"
#include "BaseController.h"
#include "CommandParser.h"
#include <queue>

class AutoController : public BaseController
{
public:
    AutoController(void);
    virtual ~AutoController(void);

    void run(void);
    bool performAction(void);
    void clearQueue(void);
private:
    CommandParser m_parser;
    std::queue<Action*> m_queue;
};
