#ifndef PATIENT_H
#define PATIENT_H

#include <map>
#include <QObject>
#include <QString>
#include <QtGlobal>

using namespace std;

class Patient : public QObject
{
    Q_OBJECT

public:
    // Constructor
    Patient(bool isAdult, int Status);

    // Getters
    bool getIsAdult();
    int getStatus();

    // Setters
    void setStatus(int newStatus);

private:
    // Private static variables
    static map<int, string> statusMap;
    static int patientCount;

    // Private variables
    int num;
    bool isAdult;
    int status;
};

#endif // PATIENT_H
