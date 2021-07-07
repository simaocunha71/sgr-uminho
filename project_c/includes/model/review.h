/**
 * @file review.h
 * @brief contém todas as funções para aceder à struct review
 * @copyright Copyright (c) 2021
 */
#ifndef REVIEWS_H
#define REVIEWS_H

/* ---------------//--------------- [Start of module review] ---------------//--------------- */

/* ---------------//--------------- [Includes] ---------------//--------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ---------------//--------------- [Defines] ---------------//--------------- */
/* [Typedefs] */
typedef struct review *REVIEW; //[struct review* -> REVIEW]

/* ---------------//--------------- [Functions] ---------------//--------------- */

/* [Initialization and destruction functions] */

/**
 * @brief Cria uma struct Review
 * @param str String onde se vai retirar os diversos elementos da struct Review
 * @return REVIEW Struct Review
 */
REVIEW create_review(char *str);

/**
 * @brief Liberta a memoria usada pela struct review
 * @param r Struct a libertar
 */
void free_review(REVIEW r);

/* [Getters functions] */

/**
 * @brief Devolve o id de uma review
 * @param r Struct Review
 * @return char* Id de uma review
 */
char* get_review_id (REVIEW r);

/**
 * @brief Devolve o id de um utilizador que fez uma review
 * @param r Struct Review
 * @return char* Id de um utilizador que fez uma review
 */
char* get_review_user_id (REVIEW r);

/**
 * @brief Devolve o id de um business que teve uma review
 * @param r Struct Review
 * @return char* Id de um business que teve uma review
 */
char* get_review_business_id (REVIEW r);

/**
 * @brief Devolve as stars de uma review
 * @param r Struct Review
 * @return float Stars de uma review
 */
float get_review_stars (REVIEW r);

/**
 * @brief Devolve o inteiro que caracteriza o grau de funny numa Review
 * @param r Struct Review
 * @return int Grau de funny numa Review
 */
int get_review_funny (REVIEW r);

/**
 * @brief Devolve o inteiro que caracteriza o grau de cool numa Review
 * @param r Struct Review
 * @return int Grau de cool numa Review
 */
int get_review_cool (REVIEW r);

/**
 * @brief Devolve o inteiro que caracteriza o grau de useful numa Review
 * @param r Struct Review
 * @return int Grau de useful numa Review
 */
int get_review_useful (REVIEW r);

/**
 * @brief Devolve a data de uma Review
 * @param r Struct Review
 * @return char* Data de uma Review
 */
char* get_review_date (REVIEW r);

/**
 * @brief Devolve o comentario numa Review
 * @param r Struct Review
 * @return char* Comentario numa Review
 */
char* get_review_text (REVIEW r);

/* ---------------//--------------- [End of module review] ---------------//--------------- */

#endif