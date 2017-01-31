//
// Created by William Gebhardt on 1/22/17.
//

#ifndef ACTIONGRAPHS_ACTION_H
#define ACTIONGRAPHS_ACTION_H


#include <vector>
#include "dependency.h"
#include "../json.hpp"
#include <iostream>

using namespace std;
using json=nlohmann::json;

class Action
{
public:


    Action(vector<shared_ptr<dependency>> dependencies);
    Action();

    dependency::condition getCondition();

    virtual void execute(vector<shared_ptr<Action>>& allActions);

    virtual void reset()
    {
        cout << "IN DEFAULT RESET" << endl;
    }

    void initAction(json& action);
protected:

    virtual bool issuable(vector<shared_ptr<Action>>& allActions);

    vector<shared_ptr<dependency>> m_dependencies;

    dependency::condition m_currentCondition;

    string m_name;

    virtual void run()
    {
        cout << "IN DEFAULT RUN" << endl;
    }


    void start(){
        m_currentCondition = dependency::Started;
    }

    void finish(){
        m_currentCondition = dependency::Finished;
    }

    void resetCondition(){
        m_currentCondition = dependency::NotStarted;
    }

    static shared_ptr<Action> generateAction(json& action);


};


#endif //ACTIONGRAPHS_ACTION_H
