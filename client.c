/**
 * @file client.c
 * @author Ömer Çaylan (omer-ceylan17@hotmail.com)
 * @brief client side c/c++ program socket programing
 * @version 0.1
 * @date 2020-03-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include "common.h"

static int n;
static int STATE = 1;
static connection_t connection;

#define MAX 80
static char buff[MAX];

void client_Create()
{
	connection.sock = socket(AF_INET, SOCK_STREAM, 0);

	if (connection.sock < 0)
	{
		printf("\nSocket Creation Error \n");
		return -1;
	}
	connection.address.sin_family = AF_INET;
	connection.address.sin_port = htons(PORT);

	if (inet_pton(AF_INET, "127.0.0.3", &connection.address.sin_addr) < 0)
	{
		printf("\n Invalid address /Address not supported\n");
		return -1;
	}

	if (connect(connection.sock, (struct sockaddr *)&connection.address, sizeof(connection.address)) < 0)
	{
		printf("Connection Failed\n");
		return -1;
	}
	else
	{
		printf("Connection to Server..\n");
	}
}

bool Client_StateOne()
{
	bzero(buff, sizeof(buff));
	printf("Print First Number: ");
	n = 0;
	while ((buff[n++] = getchar()) != '\n')
		;

	if (checkValidNumber(buff, sizeof(buff)) == -1)
	{
		write(connection.sock, reset, sizeof(reset));
		printf("%s\n", PLESE_ENTER_RIGHT_VALUE);
		return false;
	}
	write(connection.sock, buff, sizeof(buff));
	bzero(buff, sizeof(buff));
	return true;
}

bool Client_StateOperation()
{
	printf("Print Operation: ");
	n = 0;
	while ((buff[n++] = getchar()) != '\n')
		;
	if ((checkValidOperation(buff[0]) == false) || buff[1] != 10)
	{
		printf("%s\n", PLESE_ENTER_RIGHT_VALUE);
		write(connection.sock, reset, sizeof(reset));
		bzero(buff, sizeof(buff));
		return false;
	}
	write(connection.sock, buff, sizeof(buff));
	bzero(buff, sizeof(buff));
	return true;
}

bool Client_StateTwo()
{
	printf("Print Second Number: ");
	n = 0;
	while ((buff[n++] = getchar()) != '\n')
		;

	if (checkValidNumber(buff, sizeof(buff)) == -1)
	{
		write(connection.sock, reset, sizeof(reset));
		printf("%s\n", PLESE_ENTER_RIGHT_VALUE);
		return false;
	}
	write(connection.sock, buff, sizeof(buff));
	bzero(buff, sizeof(buff));
	return true;
}

bool Client_StateResult()
{
	read(connection.sock, buff, sizeof(buff));
	printf("Result: %s \n", buff);
	return true;
}

static void client_StateMachine()
{
	bool stateResponse = 0;
	while (LOOP)
	{

		switch (STATE)
		{
			
		case STATE_ONE:
			stateResponse = Client_StateOne();
			if (stateResponse)
			{
				STATE = STATE_OPERATION;
			}
			else
			{
				STATE = STATE_ONE;
			}

			break;

		case STATE_OPERATION:
			stateResponse = Client_StateOperation();
			if (stateResponse)
			{
				STATE = STATE_TWO;
			}
			else
			{
				STATE = STATE_ONE;
			}
			break;

		case STATE_TWO:
			stateResponse = Client_StateTwo();
			if (stateResponse)
			{
				STATE = STATE_RESULT;
			}
			else
			{
				STATE = STATE_ONE;
			}
			break;

		case STATE_RESULT:
			stateResponse = Client_StateResult();
			STATE = STATE_ONE;
			break;

		default:
			printf("State machine ERROR\n");
			break;
		}
	}
}

int main(int argc, char const *argv[])
{

	client_Create();
	client_StateMachine();

	return 0;
}