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


#include "client.h"

static int n;
static int STATE = 1;
static char buff[MAX];
static int serverResponse = 0;
static connection_t connection;
static bool isThereConnection = false;

static void client_Create(void)
{
	connection.sock = socket(AF_INET, SOCK_STREAM, 0);

	if (connection.sock < 0)
	{
		(void)printf("\nSocket Creation Error \n");
		return -1;
	}
	connection.address.sin_family = AF_INET;
	connection.address.sin_port = htons(PORT);

	if (inet_pton(AF_INET, "127.0.0.3", &connection.address.sin_addr) < 0)
	{
		(void)printf("\n Invalid address /Address not supported\n");
		return -1;
	}

	if (connect(connection.sock, (struct sockaddr *)&connection.address, sizeof(connection.address)) < 0)
	{
		(void)printf("Connecting to server...\n");
		isThereConnection = false;
		return -1;
	}
	else
	{
		isThereConnection = true;
		(void)printf("Connection to Server..\n");
	}
}

static void client_ConnectServer(void)
{
	if (connect(connection.sock, (struct sockaddr *)&connection.address, sizeof(connection.address)) < 0)
	{
		STATE = 6;
		isThereConnection = false;
		return -1;
	}
	else
	{
		STATE = STATE_ONE;
		isThereConnection = true;
	}
}

static bool Client_StateOne(void)
{
	if (!isThereConnection)
	{
		client_ConnectServer();
		return false;
	}

	(void)bzero(buff, sizeof(buff));
	(void)printf("Print First Number: ");
	n = 0;
	while ((buff[n++] = getchar()) != '\n')
		;

	if (checkValidNumber(buff, sizeof(buff)) == -1)
	{

		serverResponse = write(connection.sock, reset, sizeof(reset));
		(void)printf("serverResponse = %d\n", serverResponse);

		if (serverResponse == 0)
		{
			client_ConnectServer();
			return false;
		}
		(void)printf("%s\n", PLESE_ENTER_RIGHT_VALUE);
		return false;
	}
	serverResponse = write(connection.sock, buff, sizeof(buff));
	(void)printf("serverResponse = %d\n", serverResponse);

	if (serverResponse == 0)
	{
		client_ConnectServer();
		return false;
	}
	(void)bzero(buff, sizeof(buff));
	return true;
}

static bool Client_StateOperation(void)
{
	(void)printf("Print Operation: ");
	n = 0;
	while ((buff[n++] = getchar()) != '\n')
		;
	if ((checkValidOperation(buff[0]) == false) || buff[1] != 10)
	{
		(void)printf("%s\n", PLESE_ENTER_RIGHT_VALUE);
		serverResponse = write(connection.sock, reset, sizeof(reset));
		(void)printf("serverResponse = %d\n", serverResponse);
		if (serverResponse == 0)
		{
			client_ConnectServer();
			//	return false;
		}
		(void)bzero(buff, sizeof(buff));
		return false;
	}

	serverResponse = write(connection.sock, buff, sizeof(buff));

	(void)printf("serverResponse = %d\n", serverResponse);

	if (serverResponse <= 0)
	{
		client_ConnectServer();
		return false;
	}
	(void)bzero(buff, sizeof(buff));
	return true;
}

static bool Client_StateTwo(void)
{
	(void)printf("Print Second Number: ");
	n = 0;
	while ((buff[n++] = getchar()) != '\n')
		;

	if (checkValidNumber(buff, sizeof(buff)) == -1)
	{
		serverResponse = write(connection.sock, reset, sizeof(reset));
		if (serverResponse == 0)
		{
			client_ConnectServer();
			return false;
		}
		(void)printf("%s\n", PLESE_ENTER_RIGHT_VALUE);
		return false;
	}
	serverResponse = write(connection.sock, buff, sizeof(buff));
	if (serverResponse == 0)
	{
		client_ConnectServer();
		return false;
	}
	(void)bzero(buff, sizeof(buff));
	return true;
}

static bool Client_StateResult(void)
{
	serverResponse = read(connection.sock, buff, sizeof(buff));
	if (serverResponse == 0)
	{
		client_ConnectServer();
		return false;
	}
	(void)printf("Result: %s \n", buff);
	return true;
}

static void client_StateMachine(void)
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

		case WAIT_IDLE:
			client_ConnectServer();

			break;

		default:
			(void)printf("State machine ERROR\n");
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