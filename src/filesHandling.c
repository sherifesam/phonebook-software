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
void readTxtFile(void)
{
    //reading the whole file
    PTR_READ =fopen(TEXT_FILE_NAME, READ);
    // 2D-array to save the lines of the text file
    u8 line[MAX_NUMBER_OF_LINES][MAX_SIZE_OF_LINE]= {};

    // A for loop to read the whole text file and save it in the array
    u16 file_ctr = (u16)0;
    u16 size_of_line = (u16)0;
    TOTAL_LINES = (u16)0;


    while(fgets(line[file_ctr], ((s32)MAX_NUMBER_OF_LINES), PTR_READ))
    {
        size_of_line = (u16)strlen(line[file_ctr]) - (u16)1;
        line[file_ctr][size_of_line] = (u8)'\0';
        file_ctr++;
    }
    TOTAL_LINES = file_ctr;

    /* inserting the initial database into the array of structures */

    //A pointer that would point to the delimeter so that we could split the string and extract the desired data
    u8* delimeter;
    u16 lines_ctr = 1;
    u16 employees_ctr = 0;
    u16 array_ctr = 0;

    for(lines_ctr = (u16)1; lines_ctr < (TOTAL_LINES + (u16)1); lines_ctr++)
    {

        //the (-1) is because the line_ctr starts from 1 but the array indicies starts from 0
        array_ctr = lines_ctr - (u16)1;

        //finding index of the delimeter (:)
        delimeter = strchr(line[array_ctr],((s32)':'));
        u8 index = ((u32)delimeter) - ((u32)(line[array_ctr]));
        //extracting data from line
        u8 * subarr = &line[array_ctr][index + WHITE_SPACE_COMPENSATION];
        //Assigning info to the array of structures
        if((lines_ctr % (u16)3) == NAME_FIELD_INDICATION) //---------------------->  if the ctr % 3 = 1 , that means that this line contains the name field data
        {
            strcpy(RECORDS[employees_ctr].name , subarr);
        }
        else if((lines_ctr % (u16)3) == EMAIL_FIELD_INDICATION)//---------------------->  if the ctr % 3 = 2 , that means that this line contains the email field data
        {
            strcpy(RECORDS[employees_ctr].email , subarr);
        }
        else if((lines_ctr % (u16)3) == PHONE_FIELD_INDICATION)//---------------------->  if the ctr % 3 = 0 , that means that this line contains the phone number field data
        {
            strcpy(RECORDS[employees_ctr].phone , subarr);
            //every 3 lines means new employee
            employees_ctr++;
        }
        else
        {
            printf("error in reading file");
        }
    }
    fclose(PTR_READ);
}
/******************************************************************************
 *
 * Function Name: deleteEmployee
 *
 * Description: it recieves an index of the employee to be deleted, then
 *              it deletes it from the array of structure
 *
 * Arguments:   s16 index
 * Return:      void
 *
 *****************************************************************************/

void deleteEmployee(s16 index)
{
    if(index == NOT_FOUND)
    {
        printf("That employee doesn't exist in database \n");
    }
    else
    {
        //For loop to delete the desired employee and rearrange the array of struct
        u16 array_ctr;
        for(array_ctr = (u16)index; array_ctr < TOTAL_EMPLOYEES ; array_ctr++)
            {
              RECORDS[array_ctr] = RECORDS[array_ctr + (u16)1];
            } 
        printf("That employee has been deleted from the database \n");
        //Update the global variable TOTAL_LINES so that it would update the TOTAL_EMPLOYEES macro
        TOTAL_LINES = TOTAL_LINES - (u16)3;

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
 * Return:      s16
 *
 *****************************************************************************/

s16 searchForEmployee(void)
{
    u8 the_name[10] = {};
    s16 existence_ctr = 0;
    u16 array_ctr = 0;
    printf("Please enter the name of the employee \n");
    scanf("%s",the_name);
    //For loop to compare between the given name from the user and all the names in the database , it increments the ctr until it finds it
    for(array_ctr = (u16)0; array_ctr < TOTAL_EMPLOYEES; array_ctr++)
    {
        if(strcmp(RECORDS[existence_ctr].name , the_name) != 0)
            {
            existence_ctr++;
            }

    }
    // If the ctr is equal to the current number of employees, this means that the for loop couldn't find the employee which means he/she doesn't exist
    if(existence_ctr == (s16)TOTAL_EMPLOYEES)
    {
        existence_ctr = NOT_FOUND;
    }
    
    return existence_ctr;
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

void insertEmployee(void)
{
    printf("Please enter the employee's Name, Email, Phone in order : \n");
    scanf("%s%s%s", RECORDS[TOTAL_EMPLOYEES].name, RECORDS[TOTAL_EMPLOYEES].email, RECORDS[TOTAL_EMPLOYEES].phone);

    //Update the global variable TOTAL_LINES so that it would update the TOTAL_EMPLOYEES macro
    TOTAL_LINES = TOTAL_LINES + (u16)3;
    printf("This Employee has been added to the database \n");
    printf("The total number of employees is now %hu \n", TOTAL_EMPLOYEES);
}

/******************************************************************************
 *
 * Function Name: modifyEmployee
 *
 * Description: it takes an index of the employee to be modified and rewrite his
 *              name and phone number
 *
 * Arguments:   s16 index
 * Return:      void
 *
 *****************************************************************************/

void modifyEmployee(s16 index)
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

void updateTxtFile(void)
{
    u16 array_ctr=(u16)0;
    PTR_WRITE =fopen(TEXT_FILE_NAME, WRITE);
        for (array_ctr = (u16)0; array_ctr < TOTAL_EMPLOYEES; array_ctr++)
        {
            fprintf(PTR_WRITE,"Employee Name: %s\n", RECORDS[array_ctr].name);
            fprintf(PTR_WRITE,"Employee Email: %s\n", RECORDS[array_ctr].email);
            fprintf(PTR_WRITE,"Employee Phone Number: %s\n", RECORDS[array_ctr].phone);

        }
        fclose(PTR_WRITE);
}

/******************************************************************************
 *
 * Function Name: doesExist
 *
 * Description: it searches for an employee with his name in the array of 
 *              structures and make sure if it exists or not
 *
 * Arguments:   s16 index
 * Return:      void
 *
 *****************************************************************************/

void doesExist(s16 index)
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
