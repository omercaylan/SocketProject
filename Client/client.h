#ifndef CLIENT_H
#define CLIENT_H

#include "common.h"

/**
 * @brief Client create 
 * 
 */
static void client_Create(void);

/**
 * @brief Connection control
 * 
 */
static void client_ConnectServer(void);

/**
 * @brief First number input state
 * 
 * @return true 
 * @return false 
 */
static bool Client_StateOne(void);

/**
 * @brief Operation state
 * 
 * @return true 
 * @return false 
 */
static bool Client_StateOperation(void);

/**
 * @brief Second number input state  
 * 
 * @return true 
 * @return false 
 */
static bool Client_StateTwo(void);

/**
 * @brief Operation Result
 * 
 * @return true 
 * @return false 
 */
static bool Client_StateResult(void);

/**
 * @brief State machine 
 * 
 */
static void client_StateMachine(void);



#endif