/**
 * @file common.h
 * @author Ömer Çaylan (omer-ceylan17@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-03-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include <termios.h>
#include <stdbool.h>

#define PORT 8080
#define IPv4 AF_INET
#define TCP_IP_PRO SOCK_STREAM

#define STATE_ONE 1
#define STATE_TWO 2
#define STATE_OPERATION 3
#define STATE_RESULT 4

#define LOOP 1
#define MICROSECOND_CONSTANT 1000                 /**< Microsecond constant paramter to convert millis */
#define ONE_HUNDRED_MS 100 * MICROSECOND_CONSTANT /**< 100ms calculate here */


#define UNUSED(x) (void)(x) /**< Unused parameter */

#define NEW_LINE 10
#define PLESE_ENTER_RIGHT_VALUE "Please Enter Right Value"


typedef struct
{
	int sock;
	struct sockaddr address;
	int addr_len;
} connection_t;




#endif