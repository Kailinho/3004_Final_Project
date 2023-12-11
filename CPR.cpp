#include "CPR.h"

void RandomCPR(int duration){
   QElapsedTimer timer;
   timer.start();

   while (timer.elapsed() <= duration) {

       qInfo("User:*Push*");
       QCoreApplication::processEvents();
       QThread::msleep(800);
   }
}

int startCPR(AED *aed, int duration){
    qInfo("AED: Start CPR");
    QThread::sleep(1);
    RandomCPR( duration);
    emit aed->enableButton(false);
    QCoreApplication::processEvents();
    qInfo("AED: STOP CPR");
    updateAED(aed,0);
    QCoreApplication::processEvents();
    QThread::sleep(1);
    return QRandomGenerator::global()->bounded(0, 3);
}

void updateAED(AED *aed,int quality){
    if (quality == 0) emit aed->displayCompressionsSignal(0);
    else if (quality == 1) emit aed->displayCompressionsSignal(1);
    else if (quality == 2) emit aed->displayCompressionsSignal(2);
    else if (quality == 3) emit aed->displayCompressionsSignal(3);
    else if (quality == 4) emit aed->displayCompressionsSignal(4);
    QCoreApplication::processEvents();
}
void pushHarder(AED *aed){
    updateAED(aed,1);
    qInfo("AED: PUSH HARDER");

}
void goodCompressions(AED* aed){
    updateAED(aed,3);
    qInfo("AED: Good Compressions");


}
void continueCPR(AED* aed){
    updateAED(aed,2);
    qInfo("AED: Continue CPR");

}
void Release(AED* aed){
    updateAED(aed,4);
    qInfo("AED: FULLY RELEASE");

}
