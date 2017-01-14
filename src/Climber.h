/*
 * Climber.h
 *
 *  Created on: Jan 10, 2017
 *      Author: evsci_000
 */
#include "WPILib.h"
#include "constants.h"
#ifndef SRC_CLIMBER_H_
#define SRC_CLIMBER_H_

/* constants:
 *
 *
 */

class Climber
{
    public:
        enum state
        {
            OFF,
            ON
        };
        Climber(Talon * motor,
                Joystick * gamepad
        );
        virtual ~Climber();
        void stop();
        void run();
        void start();

    private:
        Talon * m_motor;
        Joystick * m_gamepad;
        state m_state;


};



#endif /* SRC_CLIMBER_H_ */