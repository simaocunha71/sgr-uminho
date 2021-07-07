/**
 * @file user.h
 * @brief contém todas as funções para aceder à struct user
 * @copyright Copyright (c) 2021
 */
#ifndef USER_H
#define USER_H

/* ---------------//--------------- [Start of module interperter] ---------------//--------------- */

/* ---------------//--------------- [Includes] ---------------//--------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ---------------//--------------- [Defines] ---------------//--------------- */
/* [Typedefs] */
typedef struct user *USER; //[struct user* -> USER]

/* ---------------//--------------- [Functions] ---------------//--------------- */

/* [Initialization and destruction functions] */

/**
 * @brief Cria uma struct User
 * @param str String onde se vai retirar os diversos elementos da struct User
 * @return USER User
 */
USER create_user(char *str);

/**
 * @brief Liberta a memoria usada pela struct dos users
 * @param u Struct a libertar
 */
void free_user(USER u);

/* [Getters functions] */

/**
 * @brief Devolve o id de um User
 * @param u Struct user
 * @return char* Id do User
 */
char* get_user_id (USER u);

/**
 * @brief Devolve o nome de um User
 * @param u Struct User
 * @return char* Nome de um User
 */
char* get_user_name (USER u);

/**
 * @brief Devolve o nome dos amigos do User
 * @param u Struct User
 * @return char* Nomes dos amigos do User
 */
char* get_user_friends (USER u);

/* ---------------//--------------- [End of module interperter] ---------------//--------------- */

#endif