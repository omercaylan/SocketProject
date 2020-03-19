/**
 * @file Timeout.h
 * @author Ömer Çaylan (omer-ceylan17@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-03-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef TIMEOUT_H
#define TIMEOUT_H

#include "../Common/common.h"

/**
 * @brief Setting counter
 * 
 * @param count 
 */
void Timeout_setCounter(int count);

/**
 * @brief Counter state 
 * 
 * @return int 
 */
int Timeout_getCounter(void);

/**
 * @brief Decrease counter
 * 
 */
void Timeout_counter(void);

/**
 * @brief Timeout control and state changes
 * 
 */
static void Timeout_control(void);

/**
 * @brief Create thread
 * 
 * @param arg 
 * @return void* 
 */
static void *TaskOne_cyclic_100ms(void *arg);

/**
 * @brief Create thread and cyclic function running
 * 
 */
void Timeout_Init(void);

#endif