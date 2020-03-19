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



#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <pthread.h>
#include <termios.h>
#include <stdbool.h>
#include "../Server/Timeout.h"

#define PORT 8080 /**<Port Number  */
#define IPv4 AF_INET
#define TCP_IP_PRO SOCK_STREAM

#define STATE_ONE 1		  /**< State one, first number input  */
#define STATE_TWO 2		  /**< State two, second number input  */
#define STATE_OPERATION 3 /**< State operation, calculate state  */
#define STATE_RESULT 4	  /**< State result */
#define WAIT_IDLE 6		  /**< Idle state */

#define LOOP 1
#define MICROSECOND_CONSTANT 1000				  /**< Microsecond constant paramter to convert millis */
#define ONE_HUNDRED_MS 100 * MICROSECOND_CONSTANT /**< 100ms calculate here */

#define UNUSED(x) (void)(x) /**< Unused parameter */

#define NEW_LINE 10 /**< New line ASCII decimal number  */
#define PLESE_ENTER_RIGHT_VALUE "Please Enter Right Value"

#define ADDITION '+'
#define SUBTRACTION '-'
#define MULTIPLICATION '*'
#define DIVISION '/'

#define MAX 80 /**<Max buffer size  */

#define reset "reset" /**< Reset keyword  */

#pragma pack(0)
typedef struct
{
	int sock;
	struct sockaddr_in address;
	int addr_len;
} connection_t;

#endif