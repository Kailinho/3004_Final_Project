#include "cpr.h"

void RandomCPR(int duration){
   QElapsedTimer timer;
   timer.start();

   while (timer.elapsed() <= duration) {
       int randomNumber = QRandomGenerator::global()->bounded(1, 10);

       qInfo("User: *Push*");

       if (randomNumber == 1){
            qInfo("AED: PUSH HARDER");
            QThread::msleep(600);
            qInfo("User: *Push*");
            qInfo("AED: GOOD COMPRESSIONS");
       } else if (randomNumber == 2){
            qInfo("AED: CONTINUE CPR");
       } else if (randomNumber == 3){
             qInfo("AED: FULLY RELEASE");
       }

       QThread::msleep(600);
   }

}

int startCPR(int duration){
    qInfo("AED: Start CPR");
    QThread::sleep(1);
    RandomCPR(duration);
    qInfo("AED: STOP CPR");
    QThread::sleep(1);
    return QRandomGenerator::global()->bounded(0, 3);
}
