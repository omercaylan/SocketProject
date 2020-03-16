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

#define PORT 8080
int sock = 0;
int valread;

struct sockaddr_in serv_addr;
char buffer[1024] = {0};

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
#define PLESE_ENTER_RIGHT_VALUE "Please Enter Right Value"
char reset[] = "reset";
void func(int sockfd)
{
	int n;
	for (;;)
	{
		bzero(buff, sizeof(buff));
		printf("Print First Number: ");
		n = 0;
		while ((buff[n++] = getchar()) != '\n')
			;
		if (checkValidNumber(buff, sizeof(buff)) == -1)
		{
			write(sockfd, reset, sizeof(reset));
			printf("%s\n", PLESE_ENTER_RIGHT_VALUE);
			continue;
		}
		write(sockfd, buff, sizeof(buff));
		bzero(buff, sizeof(buff));
		printf("Print Operation: ");
		n = 0;
		while ((buff[n++] = getchar()) != '\n')
			;
		printf("enter=%d\n", buff[0]);
		if ((checkValidOperation(buff[0]) == false) || buff[1] != 10)
		{
			printf("%s\n", PLESE_ENTER_RIGHT_VALUE);
			write(sockfd, reset, sizeof(reset));
			bzero(buff, sizeof(buff));
			continue;
		}
		write(sockfd, buff, sizeof(buff));
		bzero(buff, sizeof(buff));
		printf("Print Second Number: ");
		n = 0;
		while ((buff[n++] = getchar()) != '\n')
			;

		if (checkValidNumber(buff, sizeof(buff)) == -1)
		{
			write(sockfd, reset, sizeof(reset));
			printf("%s\n", PLESE_ENTER_RIGHT_VALUE);
			continue;
		}
		write(sockfd, buff, sizeof(buff));
		bzero(buff, sizeof(buff));

		read(sockfd, buff, sizeof(buff));
		printf("Result: %s \n", buff);
		;
	}
}

int main(int argc, char const *argv[])
{
	createClient();
	func(sock);
	return 0;
}