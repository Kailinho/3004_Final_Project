#include "CPR.h"

CPR::CPR(QObject* parent) : QObject(parent) {}

void CPR::RandomCPR(int duration)
{
    // Set the upper bound for the random number
    int r = 3;

    // Generate a random number between 1 and r

       QElapsedTimer timer;
       timer.start();

       while (timer.elapsed() <= duration) {
           int randomNumber = QRandomGenerator::global()->bounded(1, r + 1);
           if (randomNumber == 1)
                pushHarder();
           if (randomNumber == 2)
                continueCPR();
           if (randomNumber == 3)
                 goodCompressions();
           QThread::msleep(500);
       }
       goodCompressions();

}

int CPR::startCPR(int duration)
{
    qInfo("Start CPR");
    RandomCPR(duration);
    stopCPR();
    int r = 3;
    int randomNumber = QRandomGenerator::global()->bounded(1, r + 1);
    return randomNumber;
}

void CPR::continueCPR()
{
    qInfo("Continue CPR");
}

void CPR::pushHarder()
{
    qInfo("PUSH HARDER");
}

void CPR::goodCompressions()
{
    qInfo("GOOD COMPRESSIONS");
}

void CPR::stopCPR()
{
    qInfo("STOP CPR to analyse heart");
}
