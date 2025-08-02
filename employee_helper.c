#include <stdio.h>
#include "employee_helper.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

void showErrorMsg(char *msg){
    printf("\033[31m  %s\033[0m",msg);
}
void successfullMsg(char *msg){
    printf("\033[92m  %s\033[0m\n",msg);
}
void titleMsg(char *msg){
    printf("\033[94m  %s\033[0m\n",msg);
}
int validateFullName(const char *name) {
    if (name == NULL || *name == '\0') return 0;

    while (*name) {
        if (!isalpha(*name) && *name != ' ') {
            return 0;  // Invalid character found
        }
        name++;
    }

    return 1;  // All characters are valid
}

void printDepartments(){
        printf("\n    1.Testing\n");
        printf("    2.IT\n");
        printf("    3.HR\n");
        printf("    4.Finance\n");
        printf("    5.Sales\n\n");
}

const char* getDepartmentName(enum DEPARTMENT d) {
    switch (d) {
        case TESTING: return "Testing";
        case IT: return "IT";
        case HR: return "HR";
        case FINANCE: return "Finance";
        case SALES: return "Sales";
        default: return "Unknown";
    }
}

enum DEPARTMENT getDepartment(int choice) {
    switch(choice) {
        case 1: return TESTING;
        case 2: return IT;
        case 3: return HR;
        case 4: return FINANCE;
        case 5: return SALES;
        default: return -1;  // Invalid choice
    }
}

void viewEmployeeRecord(EmployeeRecord employeeRecord)
{
    titleMsg("\n  -------------------------------------------------\n");
    printf("  First Name  : %s\n",employeeRecord.firstName);
    printf("  Last  Name  : %s\n",employeeRecord.lastName);
    printf("  Employee Id : %d\n",employeeRecord.employeeId);
    printf("  Salary      : %0.2f per month\n",employeeRecord.salary);

    printf("  Department  : %s\n",getDepartmentName(employeeRecord.department));
    titleMsg("-------------------------------------------------\n");
}


void viewAllEmployees(CompanyRecord companyRecord)
{
    system("clear");
    for(int i = 0 ; i < companyRecord.noOfEmployees ; i++ )
    {
        printf("\n\033[96m------------->      Employees %d      <----------------\033[0m\n",i+1);
        viewEmployeeRecord(companyRecord.employeeRecord[i]);
    }
    wantToExitScreen();
}


void searchEmployee(CompanyRecord companyRecord)
{
    system("clear");
    char choice;
    int employeeID;
    int dep;
    titleMsg("\n\n\n     -------- Search by ------\n");
    printf("1.By Employee ID.\n");
    printf("2.Search by Name.\n");
    printf("3.Search by Department.\n\n");
    printf("           Enter your choice  : ");
  SEARCH:  scanf(" %c",&choice);
           while(getchar()!='\n');
    if(choice == '1') {
        printf("\n\nEnter the Employee ID : ");
        scanf("%d",&employeeID);
        searchEmployeeWithId(companyRecord,employeeID,1);
    } else if( choice == '2') {
        searchEmployeeWithName(companyRecord,1);
    } else if( choice == '3') {
        printf("\n\nChoose the Department from Below ");
        printDepartments();
        printf("           Enter your choice  : ");
        scanf("%d",&dep);
        searchEmployeeWithDepartments(companyRecord,dep,1);
    } else{
        showErrorMsg("Enter correct choice 1, 2, 3 : ");
        goto SEARCH;
    }
    wantToExitScreen();
}

int searchEmployeeWithId(CompanyRecord companyRecord,int employeeId,int print){
    int noOfEmployees = companyRecord.noOfEmployees;
    for(int i = 0; i < noOfEmployees; i++){
        if(employeeId == companyRecord.employeeRecord[i].employeeId){
            if(print == 1){
                viewEmployeeRecord(companyRecord.employeeRecord[i]);
                return i;
            }else{
                return i;
            }
        }
    }
    if(print == 1){ 
        printf("\n  Employee with ID : %d ",employeeId);
        showErrorMsg("not found in Employee Database\n");
    };
    return 0;
}

int searchEmployeeWithName(CompanyRecord companyRecord,int print){
    char searchName[100];
    printf("\n\nEnter the Name of Employee : ");
 NAME: fgets(searchName,100,stdin);
    if(searchName[strlen(searchName)-1]=='\n')
       searchName[strlen(searchName)-1]='\0';
    if(!validateFullName(searchName)){
        showErrorMsg("Enter Name Correctly : ");
        goto NAME;
    }
    int noOfEmployees = companyRecord.noOfEmployees;
    char fullName[100];
    for(int i = 0;i < noOfEmployees ;i++){
        sprintf(fullName,"%s %s", companyRecord.employeeRecord[i].firstName, companyRecord.employeeRecord[i].lastName);
        if(strcmp(searchName , fullName) == 0){
            if(print == 1){
                successfullMsg("\n Employee found --------------");
                viewEmployeeRecord(companyRecord.employeeRecord[i]);
                return i;
            }else{
                return i;
            }
        }
    }
    showErrorMsg("Employee Not found in the Employee Record");
    return 0;
}

int searchEmployeeWithDepartments(CompanyRecord companyRecord,enum DEPARTMENT dep,int print){
    int noOfEmployees = companyRecord.noOfEmployees;
    int count=0;
    for(int i=0;i < noOfEmployees;i++){
        if(dep == companyRecord.employeeRecord[i].department){
            if(print == 1){
                viewEmployeeRecord(companyRecord.employeeRecord[i]);
            }
            count++;
        }
    }
    return count;
}

int addEmployee(CompanyRecord *companyRecord,FILE *employeeFile)
{
      system("clear");
      companyRecord->noOfEmployees++;
      EmployeeRecord temp;
      titleMsg("\n\n ------->    Adding a new Employee    <------- \n\n");
//------first and Last Name      
      printf(" Enter the First Name : ");
  FIRSTNAME: scanf("%s",temp.firstName); 
      if(stringValidate(temp.firstName)){
            showErrorMsg("\n Enter the First name correctly : ");
            goto FIRSTNAME;
      }

      printf(" Enter the Last Name : ");
  LASTNAME: scanf("%s",temp.lastName);
      if(stringValidate(temp.lastName)){
          showErrorMsg("\n Enter the Last name correctly : ");
          goto LASTNAME;
      }

//------- Employee Id
      temp.employeeId = companyRecord->nextAvailableEmployeeId++;  
//------- Employee Salary  
       printf(" Enter the Employee Salary : ");
       scanf("%f",&temp.salary);
//------- Employee Department
       int choice;
       enum DEPARTMENT dept;

       titleMsg("\n\n Choose the Department from Below ");
       printDepartments();
       printf(" Enter your choice  : ");
    DEPT_CHOICE: scanf("%d", &choice);
       
       dept = getDepartment(choice);
       if (dept == -1) {
           showErrorMsg("Invalid department! Please choose correct from the above.\n");
           goto DEPT_CHOICE;
       }
       temp.department = dept;
        

      companyRecord->employeeRecord = (EmployeeRecord *)realloc(companyRecord->employeeRecord,(companyRecord->noOfEmployees)*sizeof(EmployeeRecord));
      if(companyRecord->employeeRecord == NULL){
          showErrorMsg("Memory Not allocated");
         return -1;
      } 
      else {
         companyRecord->employeeRecord[companyRecord->noOfEmployees -1] = temp;
         successfullMsg("\n\nAdding Employee to file\n\n");
         fseek(employeeFile,0,SEEK_END);
         if((fprintf(employeeFile, "\n%d %s %s %f %d ",temp.employeeId,temp.firstName, temp.lastName,temp.salary, temp.department)))
         {
             successfullMsg("Employee Data added to Employees Record Successfully \n");
         }
   }
   wantToExitScreen();
   return 0; 
}

void viewCompanyRecord(CompanyRecord companyRecord) {
    system("clear");

    // Header Banner
    printf("\033[48;5;255m\033[30m\n");
    printf("                                                                                              \n");
    printf("                \033[38;5;208m------>   %s   <------\033[30m                  \n", companyRecord.companyName);
    printf("                                                                                              \n\033[0m");

    // Company Profile
    printf("\n\033[1;36m     Company ID          : \033[0m%d\n", companyRecord.companyId);
    printf("\033[1;36m     Industry            : \033[0m%s\n", companyRecord.industryType);
    printf("\033[1;36m     Established         : \033[0m%d\n", companyRecord.yearEstablished);
    printf("\033[1;36m     Email               : \033[0m%s\n", companyRecord.email);
    printf("\033[1;36m     Phone               : \033[0m%s\n", companyRecord.phone);
    printf("\033[1;36m     Address             : \033[0m%s\n", companyRecord.companyAddress);
    printf("\033[1;36m     Reg. Number         : \033[0m%s\n", companyRecord.registrationNumber);
    printf("\033[1;36m     Branches            : \033[0m%d\n", companyRecord.branchCount);
    printf("\033[1;36m     Departments         : \033[0m%d\n", companyRecord.departmentsCount);
    printf("\033[1;36m     Employees           : \033[0m%d\n", companyRecord.noOfEmployees);
    // Employee Table Header
    printf("\033[37m\n---------------------------------------------------------------\033[0m\n");
    printf("\033[1;37m%-5s %-15s %-15s %-10s %-15s\033[0m\n", 
           "ID", "First Name", "Last Name", "Salary", "Department");
    printf("\033[37m---------------------------------------------------------------\033[0m\n");

    // Table Data
    for (int i = 0; i < companyRecord.noOfEmployees; i++) {
        EmployeeRecord emp = companyRecord.employeeRecord[i];
        printf("%-5d %-15s %-15s %-10.2f %-15s\n", 
               emp.employeeId, emp.firstName, emp.lastName, emp.salary, getDepartmentName(emp.department));
    }
    wantToExitScreen();
}

void exportEmployeeRecord(CompanyRecord companyRecord)
{
    system("clear");
    titleMsg("\n\n       ----->  Export Employee Record   <-----   \n\n");
    int employeeID;
    printf("\n\n Enter the Employee ID: ");
    scanf("%d", &employeeID);

    int employeeIndex = searchEmployeeWithId(companyRecord, employeeID, 1);

    if (employeeIndex == -1) {
        printf("Employee with ID %d not found.\n", employeeID);
        return;
    }

    EmployeeRecord emp = companyRecord.employeeRecord[employeeIndex];

    // Create file name: FirstName123.txt
    char fileName[100];
    sprintf(fileName, "%s%d.txt", emp.firstName, emp.employeeId);

    FILE *exportFile = fopen(fileName, "w");
    if (!exportFile) {
        printf("Failed to create report file.\n");
        return;
    }

    // Write formatted data to file
    fprintf(exportFile, "---------------------------------------\n");
    fprintf(exportFile, "           Employee Report             \n");
    fprintf(exportFile, "---------------------------------------\n");
    fprintf(exportFile, "Employee ID     : %d\n", emp.employeeId);
    fprintf(exportFile, "First Name      : %s\n", emp.firstName);
    fprintf(exportFile, "Last Name       : %s\n", emp.lastName);
    fprintf(exportFile, "Department      : %s\n", getDepartmentName(emp.department));
    fprintf(exportFile, "Salary          : %.2f\n", emp.salary);
    fprintf(exportFile, "---------------------------------------\n");

    fclose(exportFile);
    successfullMsg("Employee report exported Successfully ");
    wantToExitScreen();
}

int stringValidate(char *p) {
    int len = strlen(p);
    
    if (len < 1) {
        return 1; // Empty string = invalid
    }
    // Check all characters are alphabetic
    for (int i = 0; i < len; i++) {
        if (!isalpha(p[i])) {
            return 1; // Non-alphabet = invalid
        }
    }
    // Capitalize the first letter if not already
    if (islower(p[0])) {
        p[0] = toupper(p[0]);
    }

    return 0; // Valid
}
int numberValidate(int num) {
    if (num >= 0 && num <= 999) {
        return 0; // Valid
    }
    return 1; // Invalid
}

int validateMarks(int num) {
    if (num >= 0 && num <= 100) {
        return 0; // Valid
    }
    return 1; // Invalid
}

void wantToExitScreen(){
     char ch;
     int flag=1;
     while(1){
        printf("\n\n \033[33mPress q to exit\033[0m : ");
        scanf(" %c",&ch);
        if(ch == 'q') break;
        else showErrorMsg("              Enter q to exit the screen");
     }
}
