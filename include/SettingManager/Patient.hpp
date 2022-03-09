/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	Patient.hpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */




#ifndef PATIENT_H__
#define PATIENT_H__

#include "datatype.h"
#include <string>
using namespace std;

typedef struct patient
{
    INT16U age;
    INT16U gender;
    INT16U height;
    INT16U weight;
    bool   pacemaker;
    
    std::string id;
    std::string familyName;
    std::string firstName;

}PATIENT, *pPATIENT;


class Patient
{
public:
    Patient(/* args */);
    Patient(PATIENT pa);
    ~Patient();

    void setAge(const INT16U age);
    INT16U getAge(void);

    void setGender(const INT16U gender);
    INT16U getGender();

    void setHeight(const INT16U height);
    INT16U getHeight();

    void setWeight(const INT16U weight);
    INT16U getWeight();

    void setPacemaker(const bool pacemaker);
    bool getPacemaker();

    void setId(const std::string id);
    std::string getId();

    void setName(const std::string familyName, const std::string firstName);
    void getName(std::string &familyName, std::string firstName);

    void setPatientInfo(const PATIENT patientinfo);
    PATIENT getPatientInfo();

    INT16 savePatient();
    INT16 loadPatient();

    INT8U  clear();

private:

public:
    PATIENT patient;
};














#endif