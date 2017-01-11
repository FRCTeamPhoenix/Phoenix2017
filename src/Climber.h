/*
 * Climber.h
 *
 *  Created on: Jan 10, 2017
 *      Author: evsci_000
 */
#include "WPILib.h"
#ifndef SRC_CLIMBER_H_
#define SRC_CLIMBER_H_

/* constants:
 *
 *
 */

class Climber
{
    public:

        bool m_state;
        Climber(Talon * motor,
                Joystick * gamepad
                );
        virtual ~Climber();

        void run();

    private:
        Talon * m_motor;
        Joystick * m_gamepad;


        void stop();


};



#endif /* SRC_CLIMBER_H_ */
