#pragma once

#include "Action.h"
#include "FileStream.h"

class ActionPrint : public Action
{
public:
    ActionPrint(double value);
    void init(void);
    bool execute(void);
private:
    double m_value;
};
