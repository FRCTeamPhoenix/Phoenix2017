/*
 * Climber.h
 *
 *  Created on: Jan 10, 2017
 *      Author: evsci_000
 */
#include "WPILib.h"
#include "SmartTalon.h"
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
        enum STATE
         {
             OFF,
             ON
         };
        Climber(SmartTalon & motor);

        void setState(STATE state);
        STATE getState();
        virtual ~Climber();
        void run();

    private:
        SmartTalon & m_motor;
        STATE m_state;


};



#endif /* SRC_CLIMBER_H_ */
