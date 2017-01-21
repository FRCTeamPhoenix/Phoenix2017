/*
 * The template for any Action-derived class.
 * Do not forget to replace ActionNone with
 * whatever else you wanted.
 *
 * Please delete these comments in your code.
 */

#include "ActionNone.h"

/*
 * Always keep the Action() bit in;
 * it avoids some repetition of code.
 *
 * All actions MUST have a single double
 * as a parameter to the constructor.
 * This is enforced to make parsing
 * easier.
 */
ActionNone::ActionNone(double value)
   : Action()
{
}

/*
 * You must have m_initialized = true
 * as the last statement in your init
 * function. Otherwise, this code will
 * be repeated every time through.
 */
void
ActionNone::init(void)
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
ActionNone::execute(void)
{
   return true;
}
