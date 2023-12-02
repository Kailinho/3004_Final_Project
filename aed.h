#ifndef AED_H
#define AED_H

#include <QObject>
#include <QString>
#include <QtGlobal>
#include <QThread>
#include <QApplication>
#include <QTimer>
#include "patient.h"
#include "CPR.h"

class AED : public QObject
{
    Q_OBJECT

public:
    // Constructor
    AED();

    // Destructor
    ~AED();

    // Getters
    bool getDeviceStatus();
    void getPadsStatus();
    int getBatteryLevel();

    // Setters
    void setDeviceOn();
    void setDeviceOff();
    void setPadsStatus(bool adultPad1status, bool adultPad2status, bool childPad1status, bool childPad2status);

    // Main functions of the AED cycle
    void monitorHeart();
    void cprFeedback(int duration);
    void deliverShock();

    // Other
    void createPatient(bool isAdult, int status);

public slots:
    void updateBatteryStatus();

signals:
    void batteryLevelChanged(int level);

private:
    // Private variables
    Patient* patient;
    bool deviceStatus;
    int batteryLevel;
    bool isAdultPad1Applied;
    bool isAdultPad2Applied;
    bool isChildPad1Applied;
    bool isChildPad2Applied;
    int chargeDeliveredCount;
    CPR cpr;
};

#endif // AED_H
