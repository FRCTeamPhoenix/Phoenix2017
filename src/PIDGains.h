//
// Created by William Gebhardt on 11/19/16.
//

#ifndef INC_2017_PRESEASON_MECHANISMS_PIDGAINS_H
#define INC_2017_PRESEASON_MECHANISMS_PIDGAINS_H

class PIDGains
{
public:

    PIDGains(double P = 0, double I = 0, double D = 0, int newIZone = 0, double newFeedForward = 0);

    void set(double newP = 0, double newI = 0, double newD = 0, int newIZone = 0, double newFeedForward = 0);

    double getP();
    double getI();
    double getD();
    int getIZone();
    double getFeedForward();


    void setP(double newP);
    void setI(double newI);
    void setD(double newD);
    void setIZone(int newIZone);
    void setFeedForward(double newFeedForward);

//    void switchToGains();

private:
    double m_P = 0;

    double m_I = 0;

    double m_D = 0;

    int m_IZone = 0;

    double m_FeedForward = 0;
};
#endif //INC_2017_PRESEASON_MECHANISMS_PIDGAINS_H
