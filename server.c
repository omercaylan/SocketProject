/**
 * @file server.c
 * @author Ömer Çaylan (omer-ceylan17@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-03-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "checkValidNumber.h"
#include "common.h"

int new_socket;
int server_fd;
int valread;
struct sockaddr_in address;
int opt = 1;
int addresLen = sizeof(address);
char buffer[1024] = {0};

static const char reset[] = "reset";

char buf[80] = {0};
char operator[2] = {0};
int numberOne = 0;
int numberTwo = 0;
int result = 0;
int STATE = 1;

void CreateServer()
{
	/**Creating socket file descriptor**/
	server_fd = socket(IPv4, TCP_IP_PRO, 0);
	if (server_fd == 0)
	{
		perror("Socket Failed");
		exit(EXIT_FAILURE);
	}

	/**Forcefully attacking  socket to the port 8080**/
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	/**Forcefully attacking  socket to the port 8080**/
	if (bind(server_fd, (struct socaddr *)&address, sizeof(address)) < 0)
	{
		perror("Bind Error");
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 3) < 0)
	{
		perror("Listen Error");
		exit(EXIT_FAILURE);
	}
	new_socket = accept(server_fd, (struct socaddr *)&address, (socklen_t *)&addresLen);
	if (new_socket < 0)
	{
		perror("Accept");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("server acccept the client...\n");
	}
}
#define MAX 80

int calculator(char operation, int numberOne, int numberTwo)
{
	int result = 0;

	switch (operation)
	{
	case '+':
		result = numberOne + numberTwo;

		break;
	case '-':
		result = numberOne - numberTwo;
		break;

	case '/':
		result = numberOne / numberTwo;
		break;

	case '*':
		result = numberOne * numberTwo;
		break;

	default:
		printf("Beklenmeyen Bir Hata Oluştu\n");
		break;
	}
	return result;
}

void Server_StateOne()
{
	read(new_socket, buf, sizeof(buf));
	printf("First Number Received: %s \n", buf);
	if (strcmp(reset, buf) == 0)
	{
		STATE = STATE_ONE;
		return;
	}
	STATE = STATE_OPERATION;
	numberOne = atoi(buf);
	bzero(buf, sizeof(buf));
	return;
}

void Server_StateOperaion()
{
	read(new_socket, buf, sizeof(buf));
	if (strcmp(reset, buf) == 0)
	{
		STATE = STATE_OPERATION;
		return;
	}
	STATE = STATE_TWO;
	printf("Operation Received: %s \n", buf);
	memcpy(operator, buf, 2);
	bzero(buf, sizeof(buf));
	return;
}

void Server_StateTwo()
{
	read(new_socket, buf, sizeof(buf));
	if (strcmp(reset, buf) == 0)
	{
		STATE = STATE_TWO;
		return;
	}
	STATE = STATE_RESULT;
	printf("Operation Received: %s \n", buf);
	numberTwo = atoi(buf);
	bzero(buf, sizeof(buf));
	return;
}

void Server_StateResult()
{
	result = calculator(operator[0], numberOne, numberTwo);
	sprintf(buf, "%d", result);
	write(new_socket, buf, sizeof(buf));
	result = 0;
	bzero(buf, sizeof(buf));
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
			Server_StateOne();

			break;
		case STATE_OPERATION:
			Server_StateOperaion();

			break;
		case STATE_TWO:
			Server_StateTwo();

			break;

		case STATE_RESULT:
			Server_StateResult();

			break;

		default:
			break;
		}
	}
}

int main(int argc, char const *argv[])
{
	CreateServer();
	StateMachine();
	return 0;
}
