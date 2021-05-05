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

#include "types.h"

/*******************************************************************************
 *                           Preprocessor Definies                             *
 *******************************************************************************/
/* Calculating current number of employees in database (each 3 lines means 1 employee) */
#define TOTAL_EMPLOYEES             ((u16)(TOTAL_LINES/(u16)3))

/* Descriptive macros to remove magic numbers */
#define NAME_FIELD_SIZE             ((u16)10)
#define EMAIL_FIELD_SIZE            ((u16)30)
#define PHONE_FIELD_SIZE            ((u16)11)

#define MAX_NUMBER_OF_LINES         ((u16)150)
#define MAX_SIZE_OF_LINE            ((u16)50)
#define MAX_NUM_OF_EMPLOYEES        ((u16)50)

#define TEXT_FILE_NAME              "database.txt"
#define READ                        "r"
#define WRITE                       "w"

#define NOT_FOUND                   ((s16)-1)

#define NAME_FIELD_INDICATION       ((u16)1)
#define EMAIL_FIELD_INDICATION      ((u16)2)
#define PHONE_FIELD_INDICATION      ((u16)0)

#define WHITE_SPACE_COMPENSATION    ((u16)2)



/*******************************************************************************
 *                           User Defined Datatypes                            *
 *******************************************************************************/
typedef struct 
{
    u8 name[NAME_FIELD_SIZE];
    u8 email[EMAIL_FIELD_SIZE];
	u8 phone[PHONE_FIELD_SIZE];

}employee;

/*******************************************************************************
 *                           Extern Variables                             *
 *******************************************************************************/
extern volatile u16 TOTAL_LINES;
extern FILE *ptr_write;
extern FILE *ptr_read;
extern employee RECORDS[MAX_NUM_OF_EMPLOYEES];



/*******************************************************************************
 *                           Function Prototypes                               *
 *******************************************************************************/
void handlingChoices(void);
void deleteEmployee(s16);
void modifyEmployee(s16);
s16 searchForEmployee(void);
void updateTxtFile(void);
void insertEmployee(void);
void doesExist(s16);
void readTxtFile(void);


#endif
