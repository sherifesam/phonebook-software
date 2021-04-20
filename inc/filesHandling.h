/******************************************************************************
 *
 * File Name:   filesHandling.h
 *
 * Description: Header file for functions and definitions
 *              related to interacting with a text file database
 *
 * Date:        19/4/2021
 *
 * Author:      Sherif Esam
 ******************************************************************************/
#ifndef MY_HEADER_FILE
#define MY_HEADER_FILE



/*******************************************************************************
 *                           Preprocessor Definies                             *
 *******************************************************************************/
/* Calculating current number of employees in database (each 3 lines means 1 employee) */
#define TOTAL_EMPLOYEES         (TOTAL_LINES/3)

/* Descriptive macros to remove magic numbers */
#define NAME_FIELD_SIZE             10  
#define EMAIL_FIELD_SIZE            30  
#define PHONE_FIELD_SIZE            11  

#define MAX_NUMBER_OF_LINES         150  
#define MAX_SIZE_OF_LINE            50  
#define MAX_NUM_OF_EMPLOYEES        50  

#define TEXT_FILE_NAME              "database.txt"
#define READ                        "r"
#define WRITE                       "w"

#define NOT_FOUND                   -1

#define NAME_FIELD_INDICATION       1
#define EMAIL_FIELD_INDICATION      2
#define PHONE_FIELD_INDICATION      0

#define WHITE_SPACE_COMPENSATION    2



/*******************************************************************************
 *                           User Defined Datatypes                            *
 *******************************************************************************/
typedef struct 
{
    char name[NAME_FIELD_SIZE];
    char email[EMAIL_FIELD_SIZE];
	char phone[PHONE_FIELD_SIZE];

}employee;

/*******************************************************************************
 *                           Extern Variables                             *
 *******************************************************************************/
extern volatile int TOTAL_LINES;
extern FILE *ptr_write;
extern FILE *ptr_read;
extern employee RECORDS[MAX_NUM_OF_EMPLOYEES];



/*******************************************************************************
 *                           Function Prototypes                               *
 *******************************************************************************/
void handlingChoices();
void deleteEmployee(int);
void modifyEmployee(int);
int searchForEmployee();
void updateTxtFile();
void insertEmployee();
void doesExist(int);
void readTxtFile();


#endif