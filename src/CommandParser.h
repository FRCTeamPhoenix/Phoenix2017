#pragma once

#include <string>
#include <queue>
#include <map>
#include "Actions/Actions.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "WPILib.h"

typedef std::map<std::string, Action*(*)(double)> _pmap;

class CommandParser
{
public:
    CommandParser(std::string filename);
    ~CommandParser(void);

    void parse(std::queue<Action*>* queue);
private:
    std::fstream m_input;
    static _pmap parseMap;
};

template <class A>
Action* createAction(double value);
