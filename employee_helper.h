#ifndef __Employee_Helper__
#define __Employee_Helper__

#include <stdio.h>

enum DEPARTMENT{
     TESTING=1,IT,HR,FINANCE,SALES
};

typedef struct employeeRecord{
     int employeeId;
     char firstName[50];
     char lastName[50];
     float salary;
     enum DEPARTMENT department;
}EmployeeRecord;

typedef struct companyRecord{
        char companyName[100];
        int noOfEmployees;
        struct employeeRecord *employeeRecord;
        int nextAvailableEmployeeId;
        int companyId;
        char companyAddress[200];
        char registrationNumber[50];
        int yearEstablished;
        char email[100];
        char phone[20];
        char industryType[50];
        int departmentsCount;
        int branchCount;
}CompanyRecord;

void viewEmployeeRecord(EmployeeRecord employeeRecord);
void viewAllEmployees(CompanyRecord companyRecord);
void searchEmployee(CompanyRecord *companyRecord);
int searchEmployeeWithId(CompanyRecord *companyRecord,int employeeId,int print);
int searchEmployeeWithName(CompanyRecord *companyRecord,int print);
int searchEmployeeWithDepartments(CompanyRecord *companyRecord,enum DEPARTMENT dep,int print);
int addEmployee(CompanyRecord *companyRecord,FILE *employeeFile);
void viewCompanyRecord(CompanyRecord companyRecord);
void exportEmployeeRecord(CompanyRecord *companyRecord);
void query(CompanyRecord *companyRecord,FILE *employeeFile);
void addToFile(FILE *employeeFile,EmployeeRecord emp);

void wantToExitScreen();
int stringValidate(char *p);
int numberValidate(int num);

#endif
