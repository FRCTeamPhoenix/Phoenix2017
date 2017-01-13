#include "ActionPrint.h"

#include <WPILib.h>
#include <iostream>
#include <sstream>

ActionPrint::ActionPrint(double value)
    : Action(), m_value(value)
{
}

/*
 * You must have m_initialized = true
 * as the last statement in your init
 * function. Otherwise, this code will
 * be repeated every time through.
 */
void
ActionPrint::init(void)
{
    m_initialized = true;
}

/*
 * This function is executed for every
 * frame. When you want the action to
 * be removed from the queue, return true.
 * Otherwise, you need to return false
 * so that it won't be removed.
 */
bool
ActionPrint::execute(void)
{
    std::cout << "Printing value: " << m_value << std::endl;
    return true;
}
