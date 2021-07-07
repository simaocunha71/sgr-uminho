/* ---------------//--------------- [Start of module hashcontrol] ---------------//--------------- */
/**
 * @file hashcontrol.h
 * @brief Módulo que contém todas as funções auxiliares de acesso a tabelas de hash que intervêm 
 * nas querys pedidas
 * @copyright Copyright (c) 2021
 */
#ifndef HASHESCONTROL_H
#define HASHESCONTROL_H

/* ---------------//--------------- [Includes] ---------------//--------------- */

#include "../model/hashes.h"
#include "../view/table.h"
#include <ctype.h>

/* ---------------//--------------- [Functions] ---------------//--------------- */

/**
 * @brief Percorrendo a hashTable BUSINESSES, adiciona numa Table todos os businesses que começam pela letra letter
 * @param bs HashTable Businesses a percorrer
 * @param t Table onde se vao inserir os dados
 * @param letter Letra dos businesses que queremos saber
 */
void puts_businesses_started_by_letter_on_table (BUSINESSES bs, TABLE t, char letter);
/**
 * @brief Percorrendo a hashTable REVIEWS, calcula o valor médio das stars atribuídas a um dado business 
 * @param b Business ao qual queremos saber o valor médio das estrelas atribuidas
 * @param rs HashTable de reviews
 * @param count_reviews Array do valor das estrelas atribuidas que vai ser preenchido sempre que existir uma correspondencia entre o business_id da review e o business_id da struct Business
 * @return float Valor médio das estrelas atribuidas
 */
float average_stars_of_business(BUSINESS b, REVIEWS rs, int* count_reviews);
/**
 * @brief Percorrendo as hashTables REVIEWS e BUSINESSES, adiciona na TABLE o business_id e o business_name dos negocios com reviews feitas pelo user_id
 * @param rs HashTable REVIEWS 
 * @param bs HashTable BUSINESSES
 * @param t Table para onde se vai adicionar a informação
 * @param user_id User_id que fez as reviews
 */
void puts_businesses_reviewd_on_table (REVIEWS rs, BUSINESSES bs, TABLE t, char* user_id);
/**
 * @brief Percorrendo as hashTables REVIEWS e BUSINESSES, adiciona na TABLE os business com o valor stars nas estrelas atribuidas numa dada cidade
 * @param rs HashTable REVIEWS
 * @param bs HashTABLE BUSINESSES
 * @param t TABLE para onde se vai adicionar a informação
 * @param stars Stars de um business
 * @param city Cidade à qual se quer saber o top n de businesses
 */
void puts_businesses_with_stars_of_city_on_table (REVIEWS rs, BUSINESSES bs,TABLE t, float stars, char* city);
/**
 * @brief Percorrendo as hashTables REVIEWS e BUSINESSES, adiciona na TABLE os primeiros top businesses numa table (tendo em conta o valor de average_stars)
 * @param rs HashTable de REVIEWS
 * @param bs HashTable de BUSINESSES
 * @param t TABLE para onde se vai inserir a informação
 * @param top Numero de businesses
 */
void puts_top_businesses_on_table(REVIEWS rs, BUSINESSES bs, TABLE t, int top);
/**
 * @brief Percorrendo as hashTables REVIEWS e BUSINESSES, adiciona numa table os users que visitaram mais do que um estado 
 * @param rs HashTable de REVIEWS
 * @param bs HashTable de BUSINESSES
 * @param t TABLE para onde se vai inserir a informação
 */
void puts_international_users_on_table(REVIEWS rs, BUSINESSES bs, TABLE t);
/**
 * @brief Percorrendo a hashTable das reviews, adiciona na TABLE as reviews que contêm no campo text a palavra word
 * @param rs HashTable de REVIEWS
 * @param t Table para onde se vai inserir a informação
 * @param word Palavra a usar para filtrar reviews
 */
void puts_reviews_with_word_on_table (REVIEWS rs, TABLE t, char* word);
/**
 * @brief Percorrendo as hashTables REVIEWS e BUSINESSES, adiciona na TABLE os melhores top businesses de uma dada categoria
 * @param rs HashTable de REVIEWS
 * @param bs HashTable de BUSINESSES
 * @param t TABLE para onde se vai inserir a informação
 * @param top Inteiro referente aos melhores businesses
 * @param category Categoria para filtrar os businesses
 */
void puts_businesses_of_category_on_table(REVIEWS rs, BUSINESSES bs, TABLE t, int top, char* category);

/**
 * @brief Percorrendo a hashTable BUSINESSES, adiciona na TABLE os identificadores dos negócios e os seus nomes.
 * @param bs HashTable de BUSINESSES
 * @param t TABLE para onde se vai inserir a informação
 */
void puts_businesses_on_catalogue(BUSINESSES bs, TABLE t);


/**
 * @brief Percorrendo a hashTable USERS, adiciona na TABLE os identificadores dos utilizadores e os seus nomes.
 * @param bs HashTable de USERS
 * @param t TABLE para onde se vai inserir a informação
 */
void puts_users_on_catalogue(USERS us, TABLE t);

/**
 * @brief Percorrendo a hashTable REVIEWS, adiciona na TABLE os identificadores das reviews
 * @param bs HashTable de USERS
 * @param t TABLE para onde se vai inserir a informação
 */
void puts_reviews_on_catalogue(REVIEWS rs, TABLE t);

/* ---------------//--------------- [End of module hashcontrol] ---------------//--------------- */

#endif