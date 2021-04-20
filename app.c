/******************************************************************************
 *
 * File Name:   app.c
 *
 * Description: Source file for running an application that
 *              interacts with a textfile database
 *
 * Date:        19/4/2021
 *
 * Author:      Sherif Esam
 ******************************************************************************/

#include<stdio.h>
#include <string.h>
#include "inc/filesHandling.h"


//Global Variables
volatile int TOTAL_LINES;
FILE *ptr_write;
FILE *ptr_read;


//The capacity of the database is 50 employees
employee RECORDS[MAX_NUM_OF_EMPLOYEES];


	int main()
	{
		int choice=0;
        char restart='y';
        int index=0;
   
        readTxtFile();
        printf("\t\t\n\n----------------------------WELCOME----------------------------\t\t\n\n");
        do
        {

            printf("What do you want to do?\n");
            printf("1. Add a new employee\n");
            printf("2. Delete an employee\n");
            printf("3. Search for an employee\n");
            printf("4. Modify an employee\n");
            scanf("%d", &choice);

            switch(choice) {
            case 1:
                insertEmployee();
                updateTxtFile();
                break;
            case 2:
                index= searchForEmployee();
                deleteEmployee(index);
                updateTxtFile();
                break;
            case 3:
                index= searchForEmployee();
                doesExist(index);
                break;
            case 4:
                index= searchForEmployee();
                modifyEmployee(index);
                updateTxtFile();
                break;
            default:
                printf("Wrong entry, please enter a number between 1 and 4\n");
            }
            printf("Do you want to do anything else? (y/n) \n");
            scanf(" %c", &restart);        

            }    while(restart=='y');    
            
		return  0;
	}



