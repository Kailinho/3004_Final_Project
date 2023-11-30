#ifndef PATIENT_H
#define PATIENT_H

#include <QtGlobal>
#include <QString>
#include <QObject>

using namespace std;

class Patient : public QObject{

    Q_OBJECT

    public:
        //Public static variable
        static int p_count;

        //Constructor/destructor
        Patient(bool isAdult, bool shockable, QObject *parent = nullptr);
        ~Patient();

        //Getters
        bool getIsAdult();
        int getStatus();

        //Setters
        void setStatus(int newStatus);
    private:
        int num;
        bool isAdult;
        int status;
};

#endif // PATIENT_H
