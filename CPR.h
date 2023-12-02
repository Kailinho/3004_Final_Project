#ifndef CPR_H
#define CPR_H

#include <QObject>
#include <QString>
#include <QtGlobal>
#include <QThread>
#include <QApplication>
#include <QTimer>
#include <QCoreApplication>
#include <QRandomGenerator>
#include "patient.h"
#include <QElapsedTimer>
#include <QThread>


class CPR : public QObject
{
    Q_OBJECT

public:
    explicit CPR(QObject* parent = nullptr);
    int startCPR(int duration);
    void continueCPR();
    void pushHarder();
    void goodCompressions();
    void stopCPR();
    void RandomCPR(int duration);

};

#endif // CPR_H

