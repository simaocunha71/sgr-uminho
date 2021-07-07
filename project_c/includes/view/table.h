/**
 * @file table.h
 * @brief contém todas as funções necessárias para representar a informação oriunda das queries
 * @copyright Copyright (c) 2021
 */
#ifndef TABLE_H
#define TABLE_H

/* ---------------//--------------- [Start of module table] ---------------//--------------- */

/* ---------------//--------------- [Includes] ---------------//--------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "show.h"

/* ---------------//--------------- [Defines] ---------------//--------------- */
/* [Typedefs] */

typedef char *string; //[char* -> string]

typedef struct table *TABLE; //[struct table* -> TABLE]

/* ---------------//--------------- [Functions] ---------------//--------------- */

/* [Initialization and destruction functions] */

/**
 * @brief Inicializa uma Table
 * @param buffer_size Tamanho alocado para cada linha da TABLE
 * @return TABLE Table inicializada
 */
TABLE init_table(int buffer_size);

/**
 * @brief Elimina uma Table t
 * @param t Table a eliminar
 */
void free_table (TABLE t);

/* [Getters and setters functions] */

/**
 * @brief Devolve o tamanho de uma Table
 * @param t Table
 * @return int Tamanho de uma Table
 */
int get_table_size (TABLE t);

/**
 * @brief Devolve o numero de linhas de uma Table
 * @param t Table
 * @return int Numero de linhas de uma Table
 */
int get_table_lines(TABLE t);

/**
 * @brief Devolve o numero de colunas de uma Table
 * @param t Table
 * @return int Numero de colunas de uma Table
 */
int get_table_columns(TABLE t);

/**
 * @brief Devolve o numero de paginas
 * @param t Table
 * @return int Numero de paginas
 */
int get_table_number_of_pages (TABLE t);

/**
 * @brief Devolve o numero de linhas a desenhar por pagina
 * @param t Table 
 * @return int Numero de linhas a desenhar por pagina
 */
int get_table_lines_for_page (TABLE t);

/**
 * @brief Devolve uma copia dos titulos da coluna col de uma TABLE
 * @param t TABLE
 * @param col Coluna onde estão os titulos
 * @return char* String do titulo
 */
char* get_table_titles(TABLE t, int col);

/**
 * @brief Devolve uma copia da informaçao da coluna col de uma TABLE
 * @param t TABLE
 * @param i Index onde está a informaçao
 * @return char* String da informação
 */
char* get_table_info(TABLE t, int i);


/**
 * @brief Devolve uma copia da informaçao do título das linhas de uma TABLE
 * @param t TABLE
 * @return char* Titulo das linhas
 */
char *get_table_title_line(TABLE t);

/**
 * @brief Altera o tamanho de uma Table
 * @param t Table
 * @param size Valor do novo tamanho
 */
void set_table_size (TABLE t, int size);

/**
 * @brief Altera o numero de linhas de uma Table
 * @param t Table
 * @param lines Novo valor de linhas da Table
 */
void set_table_lines(TABLE t, int lines);

/**
 * @brief Altera o numero de colunas de uma Table
 * @param t Table
 * @param lines Novo valor de colunas da Table
 */
void set_table_columns(TABLE t, int columns);

/**
 * @brief Altera o numero de paginas de uma Table
 * @param t Table
 * @param number_of_pages Valor do novo numero de paginas 
 */
void set_table_number_of_pages(TABLE t, int number_of_pages);

/**
 * @brief Altera o numero de linhas a desenhar por pagina
 * @param t Table
 * @param lines_for_page Valor do novo numero de linhas a desenhar por pagina 
 */
void set_table_lines_for_page(TABLE t, int lines_for_page);

/**
 * @brief Coloca a informação em 10 linhas. 
 * Se a tal informação nao couber nessas linhas, incrementa-se o numero de paginas
 * @param t TABLE
 */
void set_default_pages(TABLE t);

/**
 * @brief Altera o titulo das linhas.
 * @param t Table
 * @param title Titulo das linhas.
 */
void set_title_lines(TABLE t, char* title);

/* [Increment and add functions] */

/**
 * @brief Incrementa o numero de linhas de uma Table
 * @param t Table
 */
void inc_table_lines(TABLE t);

/**
 * @brief Adiciona a string s como o titulo da coluna c da TABLE t
 * @param t TABLE
 * @param s titulo da coluna
 * @param c coluna que vai conter o titulo
 */
void add_title_of_column(TABLE t, string s, int c);

/**
 * @brief Adiciona uma string ao campo info da Table
 * @param t Table
 * @param s String a adicionar no campo info
 */
void add_info_string (TABLE t, string s);

/* [Print functions] */

/**
 * @brief Imprime a pagina page de uma TABLE
 * @param t TABLE
 * @param page Pagina a imprimir
 */
void print_page_of_table(TABLE t, int page);

/* ---------------//--------------- [End of module table] ---------------//--------------- */

#endif