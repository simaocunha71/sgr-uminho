/**
 * @file show.h
 * @brief contém todas as funções necessárias para a componente gráfica do programa
 * @copyright Copyright (c) 2021
 */
#ifndef SHOW_H
#define SHOW_H

/* ---------------//--------------- [Start of module show] ---------------//--------------- */

/* ---------------//--------------- [Includes] ---------------//--------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ---------------//--------------- [Functions] ---------------//--------------- */

void clear_screen();
void clear_line();
void show_ask_path(char mode);
void show_ask_page(char mode);
void show_menu();
void interpreter_logo();
void business_catalogue_logo();
void review_catalogue_logo();
void user_catalogue_logo();
void show_help_guide();
void show_exit_message();
void print_string_coloured (char* word_to_print, char* colour);

/* ---------------//--------------- [End of module show] ---------------//--------------- */

#endif