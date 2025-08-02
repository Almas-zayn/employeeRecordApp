#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "employee_helper.h"

CompanyRecord companyRecord = {
    .branchCount=3,
    .companyAddress="Example Address",
    .companyId=12736,
    .noOfEmployees=0,
    .nextAvailableEmployeeId = 4000,
    .departmentsCount=5,
    .email="example@gmail.com",
    .industryType="Semi Conductor",
    .registrationNumber="ABC12345",
    .phone="91 845xxxxxxx",
    .yearEstablished=2000,
    .companyName="IITM Pravartak Foundation and Technology"
};

static FILE *employeeFile;
void displayMenu();
void initEmployeesData();

int main()
{
    initEmployeesData();
    char ch = 'p';
    int flag=0;
    while(ch != 'q')
    {
        displayMenu(flag);
        scanf(" %c",&ch);
        flag=0;
        switch(ch)
        {
            case '1': viewAllEmployees(companyRecord);break;
            case '2': addEmployee(&companyRecord,employeeFile);break;
            case '3': exportEmployeeRecord(companyRecord);break;
            case '4': searchEmployee(companyRecord);break;
            case '5': viewCompanyRecord(companyRecord);break;
            default : flag=1;break;
        }
    }
    printf("\n closing the Application .....  :)  \n\n");
    fclose(employeeFile);
    return 0;
}


void initEmployeesData(){
    EmployeeRecord temp;
    int i = 0;

    employeeFile = fopen("employees_data.txt", "r+"); 
    if (employeeFile == NULL) {
        printf("File Not Opened\n");
        exit(1);
    }
    companyRecord.noOfEmployees = 0;
    rewind(employeeFile);
    while ((fscanf(employeeFile, "%d %s %s %f %d",
                  &temp.employeeId, temp.firstName,temp.lastName,
                  &temp.salary, &temp.department)) == 5) 
    {
        companyRecord.noOfEmployees++;
        companyRecord.employeeRecord = (struct employeeRecord *)realloc(companyRecord.employeeRecord, companyRecord.noOfEmployees * sizeof(EmployeeRecord));
        if (companyRecord.employeeRecord == NULL) {
            printf("Memory Reallocation Failed\n");
            fclose(employeeFile);
            exit(1);
        }
        companyRecord.employeeRecord[i] = temp;
        i++;
    }
    companyRecord.nextAvailableEmployeeId = 4000 + companyRecord.noOfEmployees;
}

void displayMenu(int flag) {
    system("clear");

    // Company name with white background and black text     
    printf("   \n\n  \033[48;5;255m\033[30m                                                                                              \n\033[0m");
    printf("  \033[48;5;255m\033[38;5;208m                ------>   %s   <------                  \n\033[0m", companyRecord.companyName);  
    printf("  \033[48;5;255m\033[30m                                                                                              \n\n\033[0m");

    // Define the options
    const char *options[18] = {
        "                      ",
        "                      ",
        " 1. View All Employee Records",
        " 2. Add Employee",
        "                      ",
        "                      ",
        "                      ",
        "                      ",
        " 3. Export Employee Record",
        " 4. Search Employee",
        "                      ",
        "                      ",
        "                      ",
        "                      ",
        " 5. View Company Record",
        "                      ",
        "                      ",
        "                      ",
    };

    // Print buttons in 3 rows and 2 columns
    printf("\n");

    for (int i = 0; i < 18; i++) {
         printf("        \033[48;5;45m\033[30m");
            printf(" %-35s ", options[i]);
            printf("\033[0m");
        if(i == 5 || i == 11 ) printf("\n");
        // New line after 2 columns
        if (i % 2 == 1)
            printf("\n");
    }

    // Exit option
    printf("\n                                                         \033[33mPress q to exit\033[0m\n");

    // Invalid input warning
    if (flag == 1) {
        printf("\033[31m\n           Please enter either 1 , 2, 3, 4, 5 or q \n\n\033[0m");
    }

    printf("       Enter your choice  : ");
}