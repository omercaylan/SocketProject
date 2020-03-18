/**
 * @file Timeout.c
 * @author Ömer Çaylan (omer-ceylan17@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-03-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "Timeout.h"

/**
 * @brief Base Counter
 * 
 */
static int localCounter = 0;

void Timeout_setCounter(int count)
{
    localCounter = count;
}

int Timeout_getCounter(void)
{
    return localCounter;
}

void Timeout_counter(void)
{
    if (localCounter > 0)
    {
        localCounter--;
    }
}

static void Timeout_control(void)
{
    if ((Server_getState() == STATE_OPERATION) && (localCounter == 0))
    {
        Server_SetState(STATE_ONE);
    }
}

static void *TaskOne_cyclic_100ms(void *arg)
{
    UNUSED(arg);
    while (true)
    {
        Timeout_counter();
        Timeout_control();
        (void)usleep(ONE_HUNDRED_MS);
    }
}

void Timeout_Init(void)
{
    int32_t result = 0;
    pthread_t threadsCyclic; // This is our thread identifier
    result = pthread_create(&threadsCyclic, NULL, TaskOne_cyclic_100ms, (void *)&threadsCyclic);
    if (result != false)
    {
        // TODO: Handle error
    }
}