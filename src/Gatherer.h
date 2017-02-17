/*
 * Gatherer.h
 *
 *  Created on: Jan 14, 2017
 *      Author: cbadu
 */

#ifndef SRC_Gatherer_H_
#define SRC_Gatherer_H_
#include "WPILib.h"
#include "constants.h"
#include "Talon.h"

class Gatherer
{
public:
    Gatherer(Talon& gathererMotor, Joystick& gamepad);
    virtual ~Gatherer();

    enum State
    {
        ON,
        OFF
    };

    void run();
    void setState(State state);

private:
    State m_state;
    Talon& m_gathererMotor;
    Joystick& m_gamepad;
};

#endif /* SRC_Gatherer_H_ */
