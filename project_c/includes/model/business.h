/**
 * @file business.h
 * @brief contém todas as funções para aceder à struct business
 * @copyright Copyright (c) 2021
 */
#ifndef BUSINESS_H
#define BUSINESS_H

/* ---------------//--------------- [Start of module business] ---------------//--------------- */

/* ---------------//--------------- [Includes] ---------------//--------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ---------------//--------------- [Defines] ---------------//--------------- */
/* [Typedefs] */
typedef struct business *BUSINESS;

/* ---------------//--------------- [Functions] ---------------//--------------- */

/* [Initialization and destruction functions] */

/**
 * @brief Cria a struct Business
 * @param str String onde se vai retirar os diversos elementos da struct Business
 * @return BUSINESS 
 */
BUSINESS create_business(char *str);

/**
 * @brief Liberta a memoria usada pela struct business
 * @param b Struct business a libertar
 */
void free_business(BUSINESS b);

/* [Getters functions] */

/**
 * @brief Devolve o id de um business
 * @param b Struct Business
 * @return char* Id de um business
 */
char *get_business_id(BUSINESS b);

/**
 * @brief Devolve o nome de business
 * @param b Struct business
 * @return char* Nome do business
 */
char* get_business_name (BUSINESS b);

/**
 * @brief Devolve a cidade de um business
 * @param b Struct business
 * @return char* Cidade do business
 */
char* get_business_city (BUSINESS b);

/**
 * @brief Devolve o estado de um business
 * @param b Struct business
 * @return char* Estado de um business
 */
char* get_business_state (BUSINESS b);

/**
 * @brief Devolve as categories de um business
 * @param b Struct business
 * @return char* Categories de um business
 */
char* get_business_categories (BUSINESS b);

/* ---------------//--------------- [Start of module business] ---------------//--------------- */

#endif