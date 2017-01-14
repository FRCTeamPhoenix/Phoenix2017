//
// Created by William Gebhardt on 11/19/16.
//

#include "PIDGains.h"

PIDGains::PIDGains(double P, double I, double D, int IZone, double FeedForward)
{
    setP(P);
    setI(I);
    setD(D);
    setIZone(IZone);
    setFeedForward(FeedForward);

}

void PIDGains::set(double newP, double newI, double newD, int newIZone, double newFeedForward)
{
    setP(newP);
    setI(newI);
    setD(newD);
    setIZone(newIZone);
    setFeedForward(newFeedForward);
}

//void PIDGains::switchToGains (SmartTalon &talon)
//{
//    talon.SetP (m_P);
//    talon.SetI (m_I);
//    talon.SetD (m_D);
//    talon.SetIzone (m_IZone);
//    talon.SetF (m_FeedForward);
//}

double PIDGains::getP()
{
    return m_P;
}

double PIDGains::getI()
{
    return m_I;
}

double PIDGains::getD()
{
    return m_D;
}

int PIDGains::getIZone()
{
    return m_IZone;
}

double PIDGains::getFeedForward()
{
    return m_FeedForward;
}

void PIDGains::setP(double newP)
{
    if (newP < 0)
    {
        m_P = 0;
    }
    else
    {
        m_P = newP;
    }
}

void PIDGains::setI(double newI)
{
    if (newI < 0)
    {
        m_I = 0;
    }
    else
    {
        m_I = newI;
    }
}

void PIDGains::setD(double newD)
{
    if (newD < 0)
    {
        m_D = 0;
    }
    else
    {
        m_D = newD;
    }
}

void PIDGains::setIZone(int newIZone)
{
    if (newIZone < 0)
    {
        m_IZone = 0;
    }
    else
    {
        m_IZone = newIZone;
    }
}

void PIDGains::setFeedForward(double newFeedForward)
{
    if (newFeedForward < 0)
    {
        m_FeedForward = 0;
    }
    else
    {
        m_FeedForward = newFeedForward;
    }
}
