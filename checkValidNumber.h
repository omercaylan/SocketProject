/**
 * @file checkValidNumber.h
 * @author Ömer Çaylan (omer-ceylan17@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-03-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief min assci number 48 = 0
 * 
 */
#define MIN_ACSII_NUMBER 48

/**
 * @brief max assci number 57 = 9
 * 
 */
#define MAX_ACSII_NUMBER 57


/**
 * @brief checking valid number 
 * (0,1,2,3,4,5,6,7,8,9)
 * @param array char array
 * @param arraySize size
 * @return int, valid 0, not valid -1 
 */
int checkValidNumber(char *array,int arraySize);

/**
 * @brief 
 * 
 * @param operator 
 * @return int 
 */
int checkValidOperation(char operator);
