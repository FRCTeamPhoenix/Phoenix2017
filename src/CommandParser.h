#pragma once

#include <string>
#include <queue>
#include <map>
#include "Actions/Actions.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "WPILib.h"

using namespace std;

typedef std::map<std::string, Action*(*)(double)> _pmap;

class CommandParser
{
public:
    CommandParser(string filename);
    ~CommandParser(void);

    void parse(std::queue<Action*>* queue);
private:
    fstream m_input;
    static _pmap parseMap;
};

template <class A>
Action* createAction(double value);
