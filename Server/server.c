/**
 * @file server.c
 * @author Ömer Çaylan (omer-ceylan17@hotmail.com)
 * @brief server side
 * @version 0.1
 * @date 2020-03-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */


#include "server.h"
#include "Timeout.h"

static int opt = 1;
static int new_socket;			/**< New socket connection */
static int result = 0;			/**< Operation result */
static int numberOne = 0;		/**< First data from client  */
static int numberTwo = 0;		/**< Second data from client */
static char buf[MAX] = {0};		/**< Data buffer read from the client  */
static char operator[2] = {0};	/**< Matematical operator buffer  */
static volatile int STATE = 1;	/**< State machine base parameter */
static int clientResponse = 0;	/**< Client response parameter */
static connection_t connection; /**< Connection base data  */

static void CreateServer(void)
{
	/**Creating socket file descriptor**/
	connection.sock = socket(IPv4, TCP_IP_PRO, 0);
	connection.addr_len = sizeof(connection.address);
	if (connection.sock == 0)
	{
		(void)printf("Socket Failed\n");
	}

	/**Forcefully attacking  socket to the port 8080**/
	if (setsockopt(connection.sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		(void)printf("setsockopt\n");
	}

	connection.address.sin_family = AF_INET;
	connection.address.sin_addr.s_addr = INADDR_ANY;
	connection.address.sin_port = htons(PORT);

	/**Forcefully attacking  socket to the port 8080**/
	if (bind(connection.sock, (struct socaddr *)&connection.address, sizeof(connection.address)) < 0)
	{
		(void)printf("Bind Error\n");
	}

	if (listen(connection.sock, 3) < 0)
	{
		(void)printf("Listen Error should be Handle here\n");
	}

	printf("Server Started… Waiting for client connection… \n");
	//FIXME: socket side
	new_socket = accept(connection.sock, (struct socaddr *)&connection.address, (socklen_t *)&connection.addr_len);
	if (new_socket < 0)
	{
		(void)printf("Accept Error should be Handle here\n");
	}
	else
	{
		(void)printf("server acccept the client...\n");
	}
}

static void waitClientConnection(void)
{
	(void)printf("Waiting Clint Connection...\n");
	new_socket = accept(connection.sock, (struct socaddr *)&connection.address, (socklen_t *)&connection.addr_len);
	if (new_socket < 0)
	{
		(void)printf("Accept Error should be Handle here\n");
	}
	else
	{
		(void)printf("server acccept the client...\n");
	}
	STATE = STATE_ONE;
}

static int calculator(char operation, int numberOne, int numberTwo)
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
		(void)printf("Beklenmeyen Bir Hata Oluştu\n");
		break;
	}
	return result;
}

static bool Server_StateOne(void)
{
	printf("debug\n");
	clientResponse = read(new_socket, buf, sizeof(buf));
	if (clientResponse == 0)
	{
		waitClientConnection();
	}
	(void)printf("First Number Received: %s \n", buf);
	if (strcmp(reset, buf) == 0)
	{
		return false;
	}
	numberOne = atoi(buf);
	(void)bzero(buf, sizeof(buf));
	Timeout_setCounter(50);
	return true;
}

static bool Server_StateOperaion(void)
{
	if (Timeout_getCounter() == 0)
	{
		(void)printf("--------->Timeout \n");
	}
	clientResponse = read(new_socket, buf, sizeof(buf));
	if (clientResponse == 0)
	{
		waitClientConnection();
	}
	if (strcmp(reset, buf) == 0)
	{
		return false;
	}
	(void)printf("Operation Received: %s \n", buf);
	memcpy(operator, buf, 2);
	(void)bzero(buf, sizeof(buf));
	return true;
}

static bool Server_StateTwo(void)
{
	clientResponse = read(new_socket, buf, sizeof(buf));
	if (clientResponse == 0)
	{
		waitClientConnection();
	}

	if (strcmp(reset, buf) == 0)
	{
		return false;
	}
	(void)printf("Operation Received: %s \n", buf);
	numberTwo = atoi(buf);
	(void)bzero(buf, sizeof(buf));
	return true;
}

static bool Server_StateResult(void)
{
	result = calculator(operator[0], numberOne, numberTwo);
	(void)printf("Result Returned: %d\n", result);
	(void)sprintf(buf, "%d", result);
	clientResponse = write(new_socket, buf, sizeof(buf));
	if (clientResponse == 0)
	{
		waitClientConnection();
	}
	result = 0;
	bzero(buf, sizeof(buf));
	STATE = STATE_ONE;
	return true;
}

//TODO: State machine should be changed,(use function pointer)
static void StateMachine(void)
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
			(void)printf("State Machine default ERROR\n");
			break;
		}
	}
}

int Server_GetState(void)
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
	Timeout_Init();
	StateMachine();

	return 0;
}
