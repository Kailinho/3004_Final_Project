#ifndef PATIENT_H
#define PATIENT_H

#include <map>
#include <QtGlobal>
#include <QString>

using namespace std;

class Patient
{
public:
    Patient(QString name, int age, int healthStatus);
    bool isAnAdult();
private:
    static map<int, string> healthCondition;
    QString name;
    int age;
    int healthStatus;
};

#endif // PATIENT_H
