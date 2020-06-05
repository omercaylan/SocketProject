#ifndef SERVER_H
#define SERVER_H

#include "../Common/common.h"
#include "../Client/client.h"
#include <stdbool.h>
#include "Timeout.h"

/**
 * @brief Create a Server object
 * 
 */
static void CreateServer(void);

/**
 * @brief 
 * 
 */
static void waitClientConnection(void);

/**
 * @brief 
 * 
 * @param operation 
 * @param numberOne 
 * @param numberTwo 
 * @return int 
 */
static int calculator(char operation, int numberOne, int numberTwo);

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
static bool Server_StateOne(void);

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
static bool Server_StateOperaion(void);

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
static bool Server_StateTwo(void);

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
static bool Server_StateResult(void);

/**
 * @brief 
 * 
 * @return int 
 */
int Server_GetState(void);

/**
 * @brief 
 * 
 * @param NewState 
 */
void Server_SetState(int NewState);

#endif