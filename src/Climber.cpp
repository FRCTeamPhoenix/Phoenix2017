/*
 * Climber.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: evsci_000
 */
#include "Climber.h"

Climber::Climber(
        Talon * motor,
        Joystick * gamepad) {
    m_motor = motor;
    m_gamepad = gamepad;
    m_state = false;

}
Climber::~Climber(){
}

void Climber::run(){

    bool m_climb = m_gamepad->GetRawButton(buttonNames::buttonA);

    switch (m_climb){
            if(m_climb){
                m_motor->Set(1.0f);
            } else {
                stop();
            }
            }





    //WE NEED STOP METHOD


}









