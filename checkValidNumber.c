
#include "checkValidNumber.h"
#include <stdbool.h>

int checkValidNumber(char *array, int arraySize)
{
    int result = 0;
    for (int i = 0; i < arraySize; i++)
    {
        if (((array[i] < MIN_ACSII_NUMBER) && (array[i] > 10)) || (array[i] > MAX_ACSII_NUMBER))
        {
            result = -1;
            break;
        }
    }
    return result;
}

char validOperation[] = {'+', '-', '*', '/'};

int checkValidOperation(char operator)
{
    for (int i = 0; i < sizeof(validOperation); i++)
    {
        if (operator== validOperation[i])
        {
            return true;
        }
    }
    return false;
}
/*
int main()
{

#define ONE 1
#define TWO 2
#define THREE 3
    int STATE = 1;
    while (1)
    {

        switch (STATE)
        {
        case ONE:
            break;
        case TWO:
            break;
        case THREE:
            break;

        default:
            break;
        }
    }
}
*/
