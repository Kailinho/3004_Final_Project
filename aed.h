#ifndef AED_H
#define AED_H

#include <QString>
#include <QtGlobal>
#include <QThread>
#include <QObject>
#include <QLabel>
#include <QPixmap>
#include "patient.h"

class AED : public QObject{

    Q_OBJECT

    public:
        //Constructor/deconstructor
        AED(QObject *parent = nullptr);
        ~AED();

        //Getters
        bool getPower();
        int getBatteryLevel();

        //Setters
        void togglePower();
        void setPadsStatus(bool adultPad1status, bool adultPad2status, bool childPad1status, bool childPad2status);

        // Main functions of the AED cycle
        void checkPads();
        void monitorHeart();
        void deliverShock();
        void cprFeedback(int duration);

        // Others
        void createPatient(bool isAdult, int status);


    signals:
        void batteryLevelChanged(int level);
        void shockCountChanged(int shockCount);
        void displayHRSignal(int status);
        void displayCompressionsSignal(int quality);
        void enableButton(bool value);
   public slots:
        void badCPRClicked();
        void okCPRClicked();
        void goodCPRClicked();
        void releaseClicked();

    private:
        bool isOn;
        QPair <bool, bool> adultPads;
        QPair <bool, bool> childPads;
        int batteryLevel;
        int shockCount;
        Patient* patient;
};

#endif // AED_H
