/* ---------------//--------------- [Start of module interperter] ---------------//--------------- */
/**
 * @file interpreter.h
 * @brief contém todas as funções necessárias para o interpretador de comandos, 
 * assim como as outras funcionalidades para o menu 
 * @copyright Copyright (c) 2021
 */
#ifndef INTERPRETER_H
#define INTERPRETER_H

/* ---------------//--------------- [Defines] ---------------//--------------- */

#define BUF_SIZE 200

/* ---------------//--------------- [Includes] ---------------//--------------- */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "sgr.h"
#include "../view/show.h"

/* ---------------//--------------- [Functions] ---------------//--------------- */

/**
 * @brief Função que controla o menu.
 */
void menu();

/* ---------------//--------------- [Enf of module interperter] ---------------//--------------- */

#endif