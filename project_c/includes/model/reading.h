/**
 * @file reading.h
 * @brief contém todas as funções para aceder à struct reading
 * @copyright Copyright (c) 2021
 */
#ifndef READING_H
#define READING_H

/* ---------------//--------------- [Start of module reading] ---------------//--------------- */

/* ---------------//--------------- [Includes] ---------------//--------------- */
#include "hashes.h"


/* ---------------//--------------- [Functions] ---------------//--------------- */

/* [Loading functions] */

/**
 * @brief Carrega para uma HashTable de Users os dados de um ficheiro
 * @param filename Ficheiro com os Users
 * @param users HashTable de Users
 * @return int 1 se carregou, -1 caso o ficheiro não exista.
 */
int load_user(char *filename, USERS us);

/**
 * @brief Carrega para uma HashTable de Reviews os dados de um ficheiro
 * @param filename Ficheiro com os Reviews
 * @param rs HashTable de Reviews
 * @return int 1 se carregou, -1 caso o ficheiro não exista.
 */
int load_reviews(char *filename, REVIEWS rs, BUSINESSES bs, USERS us);

/**
 * @brief Carrega para uma HashTable de businesses os dados de um ficheiro
 * @param filename Ficheiro com os businesses
 * @param bs HashTable de businesses
 * @return int 1 se carregou, -1 caso o ficheiro não exista.
 */
int load_business(char *filename, BUSINESSES bs);

/* ---------------//--------------- [End of module reading] ---------------//--------------- */

#endif