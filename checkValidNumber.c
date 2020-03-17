
#include "checkValidNumber.h"
#include <stdbool.h>
#include "common.h"

char validOperation[] = {'+', '-', '*', '/'};

int checkValidNumber(char *array, int arraySize)
{
    int result = 0;
    for (int i = 0; i < arraySize; i++)
    {
        if (((array[i] < MIN_ACSII_NUMBER) && (array[i] > NEW_LINE)) || (array[i] > MAX_ACSII_NUMBER))
        {
            result = -1;
            break;
        }
    }
    return result;
}

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


    int STATE = 1;
    while (LOOP)
    {

        switch (STATE)
        {
        case STATE_ONE:


            break;
        case STATE_OPERATION:


            break;
        case STATE_TWO:


            break;

        default:
            break;
        }
    }
}
*/