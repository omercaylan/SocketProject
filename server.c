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

#include "checkValidNumber.h"
#include "common.h"

int opt = 1;
int new_socket;
static connection_t connection;

char buffer[1024] = {0};

char buf[80] = {0};
char operator[2] = {0};
int numberOne = 0;
int numberTwo = 0;
int result = 0;
int STATE = 1;

void CreateServer()
{
	/**Creating socket file descriptor**/
	connection.sock = socket(IPv4, TCP_IP_PRO, 0);
	connection.addr_len = sizeof(connection.address);
	if (connection.sock == 0)
	{
		printf("Socket Failed\n");
	}

	/**Forcefully attacking  socket to the port 8080**/
	if (setsockopt(connection.sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		printf("setsockopt\n");
	}

	connection.address.sin_family = AF_INET;
	connection.address.sin_addr.s_addr = INADDR_ANY;
	connection.address.sin_port = htons(PORT);

	/**Forcefully attacking  socket to the port 8080**/
	if (bind(connection.sock, (struct socaddr *)&connection.address, sizeof(connection.address)) < 0)
	{
		printf("Bind Error\n");
	}

	if (listen(connection.sock, 3) < 0)
	{
		printf("Listen Error should be Handle here\n");
	}

	printf("Server Started… Waiting for client connection… \n");
	//FIXME: socket side
	new_socket = accept(connection.sock, (struct socaddr *)&connection.address, (socklen_t *)&connection.addr_len);
	if (new_socket < 0)
	{
		printf("Accept Error should be Handle here\n");
	}
	else
	{
		printf("server acccept the client...\n");
	}
}

int calculator(char operation, int numberOne, int numberTwo)
{
	int result = 0;

	switch (operation)
	{
	case ADDITION:
		result = numberOne + numberTwo;

		break;
	case SUBTRACTION:
		result = numberOne - numberTwo;
		break;

	case MULTIPLICATION:
		result = numberOne * numberTwo;
		break;

	case DIVISION:
		result = numberOne / numberTwo;
		break;

	default:
		printf("Beklenmeyen Bir Hata Oluştu\n");
		break;
	}
	return result;
}

bool Server_StateOne()
{
	read(new_socket, buf, sizeof(buf));
	printf("First Number Received: %s \n", buf);
	if (strcmp(reset, buf) == 0)
	{
		return false;
	}
	numberOne = atoi(buf);
	bzero(buf, sizeof(buf));
	Timeout_setCounter(50);
	return true;
}

bool Server_StateOperaion()
{
	if (Timeout_getCounter() == 0)
	{
		printf("--------->Timeout \n");
	}
	read(new_socket, buf, sizeof(buf));
	if (strcmp(reset, buf) == 0)
	{
		return false;
	}
	printf("Operation Received: %s \n", buf);
	memcpy(operator, buf, 2);
	bzero(buf, sizeof(buf));
	return true;
}

bool Server_StateTwo()
{
	read(new_socket, buf, sizeof(buf));
	if (strcmp(reset, buf) == 0)
	{
		return false;
	}
	printf("Operation Received: %s \n", buf);
	numberTwo = atoi(buf);
	bzero(buf, sizeof(buf));
	return true;
}

bool Server_StateResult()
{
	result = calculator(operator[0], numberOne, numberTwo);
	printf("Result Returned: %d\n", result);
	sprintf(buf, "%d", result);
	write(new_socket, buf, sizeof(buf));
	result = 0;
	bzero(buf, sizeof(buf));
	STATE = STATE_ONE;
	return true;
}

static void StateMachine()
{
	bool stateResponse = 0;
	while (LOOP)
	{
		switch (STATE)
		{

		case STATE_ONE:
			stateResponse = Server_StateOne();
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
			stateResponse = Server_StateOperaion();
			if (stateResponse)
			{
				STATE = STATE_TWO;
			}
			else
			{
				STATE = STATE_OPERATION;
			}
			break;

		case STATE_TWO:
			stateResponse = Server_StateTwo();
			if (stateResponse)
			{
				STATE = STATE_RESULT;
			}
			else
			{
				STATE = STATE_TWO;
			}
			break;

		case STATE_RESULT:
			stateResponse = Server_StateResult();
			STATE = STATE_ONE;

			break;

		default:
			printf("State Machine default ERROR\n");
			break;
		}
	}
}

int Server_getState()
{
	return STATE;
}

void Server_SetState(int NewState)
{
	STATE = NewState;
}

int main(int argc, char const *argv[])
{

	CreateServer();
	//TODO: Timeout fonction will be call
	Timeout_Init();
	StateMachine();

	return 0;
}
