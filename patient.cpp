#include "patient.h"

// Static variables
map<int, string> statusMap = {{0, "Dead"}, {1, "Stable"}, {2, "V-Fib"}, {3, "V-Tach"}};

int Patient::patientCount = 0;

// Constructor
Patient::Patient(bool isAdult, int status): QObject(){
    num = patientCount++;
    this->isAdult = isAdult;
    this->status = status;

    if(isAdult){
        qInfo("Patient %i is an adult.", num);
    } else {
        qInfo("Patient %i is a child.", num);
    }
}

//Getters
bool Patient::getIsAdult(){
    return isAdult;
}

int Patient::getStatus(){
    return status;
}

//Setters
void Patient::setStatus(int newStatus){
    status = newStatus;
}
