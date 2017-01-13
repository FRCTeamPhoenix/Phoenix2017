#include "CommandParser.h"

#include <iostream>
#include <sstream>
#include <WPILib.h>

#define ACTION_PAIR(n) {#n, createAction<n>}

/* Add ACTION_PAIR for every existing action. */
_pmap CommandParser::parseMap =
{
    ACTION_PAIR(ActionNone),
    ACTION_PAIR(ActionPrint),
};

CommandParser::CommandParser(std::string filename)
    : m_input(filename)
{
}

CommandParser::~CommandParser(void)
{}

void
CommandParser::parse(std::queue<Action*>* queue)
{
    // SmartDashboard::PutString("DB/String 7", "Blah");
    std::string line;
    int currentLine = 0;
    while (std::getline(m_input, line))
    {
        std::cout << line << std::endl;
        currentLine++;
        if (line.length() == 0)
            continue;

        try
        {
            std::stringstream split(line);
            std::string actionName;
            double value;
            split >> actionName >> value;

            if (Action* (*generator)(double) = parseMap[actionName])
                queue->push(generator(value));
            else
                std::cerr << "Found nonexistent command at line "
                          << currentLine << "." << std::endl;

            if (split.peek() == EOF)
                std::cerr << "Found garbage at end of line "
                          << currentLine << "." << std::endl;
        }
        catch (...)
        {
            std::cerr << "Failed to parse line " << currentLine << "." << std::endl;
        }
    }
}

/*
 * Template utility that creates an action type
 * as passed in to the template.
 *
 * Used as a function pointer.
 */
template <class A>
Action*
createAction(double value)
{
    return new A(value);
}
