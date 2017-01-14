#include "AutoController.h"

#include <iostream>
#include <WPILib.h>

AutoController::AutoController(void)
    : m_parser("/home/lvuser/auto.txt")
{
    m_parser.parse(&m_queue);
}

AutoController::~AutoController(void)
{
}

void
AutoController::run(void)
{
    /* TODO: Make Y button clear queue of robot. */
    performAction();
}

/*
 * Returns false if queue is empty.
 */
bool
AutoController::performAction(void)
{
    if (m_queue.empty())
    {
	return false;
    }

    Action *currentAction = m_queue.front();
    if (!currentAction->isInitialized())
	currentAction->init();
    /* Execute returns true if finished */
    if (currentAction->execute())
    {
	delete currentAction;
	m_queue.pop();
    }

    return true;
}

/*
 * Simple utility function to clear Action queue.
 */
void
AutoController::clearQueue()
{
    while (!m_queue.empty())
    {
	delete m_queue.front();
	m_queue.pop();
    }
}
