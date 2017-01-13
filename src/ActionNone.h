#pragma once

#include "Action.h"

class ActionNone : public Action
{
public:
    ActionNone(double value);
    void init(void);
    bool execute(void);
};
