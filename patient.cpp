#include "patient.h"

int Patient::p_count = 1;

Patient::Patient(bool isAdult, int status, QObject *parent): QObject(parent){
    num = p_count;
    p_count++;

    this->isAdult = isAdult;
    this->status = status;

    // This can probably be removed once a dropdown menu has been created with multiple patients
    if(isAdult){
        qInfo("Patient %i is an adult.", num);
    } else {
        qInfo("Patient %i is a child.", num);
    }
}

Patient::~Patient(){}

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
