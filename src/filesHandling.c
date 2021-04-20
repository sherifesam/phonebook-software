/******************************************************************************
 *
 * File Name:   filesHandling.c
 *
 * Description: Source file for functions and definitions
 *              related to interacting with a text file database
 *              it mainly depends on reading the whole text file 
 *              and do some string manipulation to extract the data 
 *              from the lines, then it saves all the data in an array
 *              structures, so that all the processing the user wants
 *              would happen on the array then the program would
 *              update the text file after each operation.
 *
 * Date:        19/4/2021
 *
 * Author:      Sherif Esam
 ******************************************************************************/

#include <stdio.h>
#include <string.h>
#include "../inc/filesHandling.h"

/******************************************************************************
 *
 * Function Name: readTxtFile
 *
 * Description: it reads all the lines in the text file and save it, then
 *              it extracts the desired data from these lines and assign it 
 *              to the array of structures.
 *
 * Arguments:   None
 * Return:      void
 *
 *****************************************************************************/
void readTxtFile()
{
    //reading the whole file
    ptr_read =fopen(TEXT_FILE_NAME, READ);
    // 2D-array to save the lines of the text file
    char line[MAX_NUMBER_OF_LINES][MAX_SIZE_OF_LINE];

    // A for loop to read the whole text file and save it in the array
    int i=0;
    TOTAL_LINES = 0;
    while(fgets(line[i], MAX_NUMBER_OF_LINES, ptr_read)) 
    {
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }
    TOTAL_LINES = i;

    /* inserting the initial database into the array of structures */

    //A pointer that would point to the delimeter so that we could split the string and extract the desired data
    char* delimeter;  
    int lines_ctr=1;
    int employees_ctr=0;
    for(lines_ctr=1; lines_ctr< (TOTAL_LINES+1); lines_ctr++)
    {
        //finding index of the delimeter (:)
        delimeter = strchr(line[lines_ctr - 1],':'); //-----------------> the (-1) is because the line_ctr starts from 1 but the array indicies starts from 0
        int index = (int)(delimeter - line[lines_ctr - 1]);
        //extracting data from line
        char * subarr= &line[lines_ctr - 1][index + WHITE_SPACE_COMPENSATION];
        //Assigning info to the array of structures
        if(lines_ctr % 3 == NAME_FIELD_INDICATION) //---------------------->  if the ctr % 3 = 1 , that means that this line contains the name field data
        {
            strcpy(RECORDS[employees_ctr].name , subarr);
        }
        else if(lines_ctr % 3 == EMAIL_FIELD_INDICATION)//---------------------->  if the ctr % 3 = 2 , that means that this line contains the email field data
        {
            strcpy(RECORDS[employees_ctr].email , subarr);
        }
        else if(lines_ctr % 3 == PHONE_FIELD_INDICATION)//---------------------->  if the ctr % 3 = 0 , that means that this line contains the phone number field data
        {
            strcpy(RECORDS[employees_ctr].phone , subarr);
            //every 3 lines means new employee
            employees_ctr++;
        }
    }
    fclose(ptr_read);
}
/******************************************************************************
 *
 * Function Name: deleteEmployee
 *
 * Description: it recieves an index of the employee to be deleted, then
 *              it deletes it from the array of structure
 *
 * Arguments:   int index
 * Return:      void
 *
 *****************************************************************************/

void deleteEmployee(int index)
{
    if(index == NOT_FOUND)
    {
        printf("That employee doesn't exist in database \n");
    }
    else
    {
        //For loop to delete the desired employee and rearrange the array of struct
        int j;
        for(j = index; j < TOTAL_EMPLOYEES ; j++)
            {
              RECORDS[j] = RECORDS[j + 1];
            } 
        printf("That employee has been deleted from the database \n");
        //Update the global variable TOTAL_LINES so that it would update the TOTAL_EMPLOYEES macro
        TOTAL_LINES = TOTAL_LINES - 3;

    }
   
}

/******************************************************************************
 *
 * Function Name: searchForEmployee
 *
 * Description: it asks the user to enter the name of the employee he/she wants
 *              to search for, then it search for it and returns it's index in 
 *              array of structures
 *
 * Arguments:   None
 * Return:      int
 *
 *****************************************************************************/

int searchForEmployee()
{
    char * theName;
    int cnt=0;
    int t=0;
    printf("Please enter the name of the employee \n");
    scanf("%s",theName);
    //For loop to compare between the given name from the user and all the names in the database , it increments the ctr until it finds it
    for(t=0; t< TOTAL_EMPLOYEES; t++)
    {
        if(strcmp(RECORDS[cnt].name , theName) != 0)
            {
                cnt++;   
            }

    }
    // If the ctr is equal to the current number of employees, this means that the for loop couldn't find the employee which means he/she doesn't exist
    if(cnt == TOTAL_EMPLOYEES)
    {
        cnt= NOT_FOUND;
    }
    
    return cnt;
}

/******************************************************************************
 *
 * Function Name: insertEmployee
 *
 * Description: it asks the user for the new employee data and adds it to the  
 *              array of structures
 *
 * Arguments:   None
 * Return:      void
 *
 *****************************************************************************/

void insertEmployee()
{
    printf("Please enter the employee's Name, Email, Phone in order : \n");
    scanf("%s%s%s", RECORDS[TOTAL_EMPLOYEES].name, RECORDS[TOTAL_EMPLOYEES].email, RECORDS[TOTAL_EMPLOYEES].phone);

    //Update the global variable TOTAL_LINES so that it would update the TOTAL_EMPLOYEES macro
    TOTAL_LINES = TOTAL_LINES + 3;
    printf("This Employee has been added to the database \n");
    printf("The total number of employees is now %d \n", TOTAL_EMPLOYEES);
}

/******************************************************************************
 *
 * Function Name: modifyEmployee
 *
 * Description: it takes an index of the employee to be modified and rewrite his
 *              name and phone number
 *
 * Arguments:   int index
 * Return:      void
 *
 *****************************************************************************/

void modifyEmployee(int index)
{
    if(index == NOT_FOUND)
    {
        printf("That employee doesn't exist in database \n");
    }
    else
    {
        printf("Please enter the employee's new Email and phone number in order : \n");
        scanf("%s%s", RECORDS[index].email, RECORDS[index].phone);
    }
   
}

/******************************************************************************
 *
 * Function Name: updateTxtFile
 *
 * Description: it takes all the data on the array of structre and write it 
 *              in the text file in a readable way
 *
 * Arguments:   None
 * Return:      void
 *
 *****************************************************************************/

void updateTxtFile()
{
    int i=0;
    ptr_write =fopen(TEXT_FILE_NAME, WRITE);
        for (i=0; i< TOTAL_EMPLOYEES; i++)
        {
            fprintf(ptr_write,"Employee Name: %s\n", RECORDS[i].name);
            fprintf(ptr_write,"Employee Email: %s\n", RECORDS[i].email);
            fprintf(ptr_write,"Employee Phone Number: %s\n", RECORDS[i].phone);

        }
        fclose(ptr_write);
}

/******************************************************************************
 *
 * Function Name: doesExist
 *
 * Description: it searches for an employee with his name in the array of 
 *              structures and make sure if it exists or not
 *
 * Arguments:   int index
 * Return:      void
 *
 *****************************************************************************/

void doesExist(int index)
{
    if(index == NOT_FOUND)
    {
        printf("This employee doesn't exist in the database \n");
    }
    else
    {
        printf("This employee does exist and he/she is currently the employee number %d in the database\n", (index+1)); //----> this(+1) is because the array indicies starts from 0, 
    }                                                                                                                   // but the employees counting logically starts from 1

}