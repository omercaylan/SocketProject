
#include "checkValidNumber.h"
#include <stdbool.h>
#include "common.h"

static char validOperation[] = {ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION};

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
