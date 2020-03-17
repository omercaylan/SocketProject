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

int sock = 0;
int valread;
static int STATE = 1;

struct sockaddr_in serv_addr;
char buffer[1024] = {0};
int n;

void createClient()
{
	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock < 0)
	{
		printf("\nSocket Creation Error \n");
		return -1;
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	if (inet_pton(AF_INET, "127.0.0.3", &serv_addr.sin_addr) < 0)
	{
		printf("\n Invalid address /Address not supported\n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("Connection Failed\n");
		return -1;
	}
	else
	{
		printf("Connection to Server..\n");
	}
}

#define MAX 80
char buff[MAX];
static char reset[] = "reset";

void Client_StateOne()
{
	bzero(buff, sizeof(buff));
	printf("Print First Number: ");
	n = 0;
	while ((buff[n++] = getchar()) != '\n')
		;

	if (checkValidNumber(buff, sizeof(buff)) == -1)
	{
		write(sock, reset, sizeof(reset));
		printf("%s\n", PLESE_ENTER_RIGHT_VALUE);
		STATE = STATE_ONE;
		return;
	}
	write(sock, buff, sizeof(buff));
	bzero(buff, sizeof(buff));
	STATE = STATE_OPERATION;
	return;
}

void Client_StateOperation()
{
	printf("Print Operation: ");
	n = 0;
	while ((buff[n++] = getchar()) != '\n')
		;
	if ((checkValidOperation(buff[0]) == false) || buff[1] != 10)
	{
		printf("%s\n", PLESE_ENTER_RIGHT_VALUE);
		write(sock, reset, sizeof(reset));
		bzero(buff, sizeof(buff));
		STATE = STATE_ONE;
		return;
	}
	write(sock, buff, sizeof(buff));
	bzero(buff, sizeof(buff));
	STATE = STATE_TWO;
	return;
}

void Client_StateTwo()
{
	printf("Print Second Number: ");
	n = 0;
	while ((buff[n++] = getchar()) != '\n')
		;

	if (checkValidNumber(buff, sizeof(buff)) == -1)
	{
		write(sock, reset, sizeof(reset));
		printf("%s\n", PLESE_ENTER_RIGHT_VALUE);
		STATE = STATE_ONE;
		return;
	}
	write(sock, buff, sizeof(buff));
	bzero(buff, sizeof(buff));
	STATE = STATE_RESULT;
	return;
}

void Client_StateResult()
{

	read(sock, buff, sizeof(buff));
	printf("Result: %s \n", buff);
	STATE = STATE_ONE;
	return;
}

static void StateMachine()
{

	while (LOOP)
	{

		switch (STATE)
		{
		case STATE_ONE:
			Client_StateOne();

			break;
		case STATE_OPERATION:
			Client_StateOperation();

			break;
		case STATE_TWO:
			Client_StateTwo();

			break;

		case STATE_RESULT:
			Client_StateResult();

			break;

		default:
			break;
		}
	}
}

int main(int argc, char const *argv[])
{

	createClient();
	StateMachine();

	return 0;
}