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
#include "inc/types.h"


//Global Variables
volatile u16 TOTAL_LINES;
FILE *ptr_write;
FILE *ptr_read;


//The capacity of the database is 50 employees
employee RECORDS[MAX_NUM_OF_EMPLOYEES];


	u16 main(void)
	{
		u16 choice = 0;
        u8 restart = 'y';
        s16 index = 0;
   
        readTxtFile();
        printf("\t\t\n\n----------------------------WELCOME----------------------------\t\t\n\n");
        do
        {

            printf("What do you want to do?\n");
            printf("1. Add a new employee\n");
            printf("2. Delete an employee\n");
            printf("3. Search for an employee\n");
            printf("4. Modify an employee\n");
            scanf("%hu", &choice);

            switch(choice) {
            case (u16)1:
                insertEmployee();
                updateTxtFile();
                break;
            case (u16)2:
                index= searchForEmployee();
                deleteEmployee((s16)index);
                updateTxtFile();
                break;
            case (u16)3:
                index= searchForEmployee();
                doesExist((s16)index);
                break;
            case (u16)4:
                index= searchForEmployee();
                modifyEmployee((s16)index);
                updateTxtFile();
                break;
            default:
                printf("Wrong entry, please enter a number between 1 and 4\n");
                break;
            }
            printf("Do you want to do anything else? (y/n) \n");
            scanf(" %c", &restart);        

            }    while(restart==(u8)'y');
            
		return (u16)0;
	}



