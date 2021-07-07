/**
 * @file hashes.h
 * @brief contém todas as funções para aceder às diferentes tabelas de hash
 * @copyright Copyright (c) 2021
 */
#ifndef HASHES_H
#define HASHES_H

/* ---------------//--------------- [Start of module hashes] ---------------//--------------- */

/* ---------------//--------------- [Includes] ---------------//--------------- */

#include "user.h"
#include "review.h"
#include "business.h"
#include "glibWarningAvoid.h"

/* ---------------//--------------- [Defines] ---------------//--------------- */

typedef struct hashdata *HASHDATA;
typedef GHashTable* USERS;      //[hashtable* -> USERS]
typedef GHashTable* REVIEWS;	//[hashtable* -> REVIEWS]
typedef GHashTable* BUSINESSES; //[hashtable* -> BUSINESSES]

/* ---------------//--------------- [Functions] ---------------//--------------- */

/* [Initialization and destruction functions] */

/**
 * @brief Inicializa uma hashTable de Businesses
 * @return BUSINESSES HashTable de Businesses
 */
BUSINESSES init_businesses ();

/**
 * @brief Liberta a memoria usada pela hashTable de businesses
 * @param bs HashTable de Businesses a libertar
 */
void destroy_businesses(BUSINESSES bs);

/**
 * @brief Inicializa uma hashTable de Reviews
 * @return REVIEWS HashTable de reviews
 */
REVIEWS init_reviews();

/**
 * @brief Liberta a memoria usada pela hashTable de reviews
 * @param rs HashTable de reviews a libertar
 */
void destroy_reviews(REVIEWS rs);

/**
 * @brief Inicializa uma hashTable de Users
 * @return USERS HashTable de users
 */
USERS init_users ();

/**
 * @brief Liberta a memoria usada pela hashTable de users
 * @param us hashTable de users a libertar
 */
void destroy_users(USERS us);

/**
 * @brief Inicializa uma HashData
 * @return HASHDATA HashData inicializada
 */
HASHDATA init_hashdata ();

/**
 * @brief Liberta a memória usada por uma hashData
 * @param hd HashData a libertar
 */
void free_hashdata (HASHDATA hd);

/**
 * @brief Devolve uma hashData com alguns campos da struct business - necessária para a resolução de algumas queries
 * @param b Struct Business 
 * @return HASHDATA HashData com dados da struct business
 */
HASHDATA create_hashdata_business(BUSINESS b);

/**
 * @brief Cria uma tabela de hash da API do GLIB
 * @return GHashTable* Tabela de hash criada
 */
GHashTable * create_hashtable_of_hd();

/**
 * @brief Liberta a memória usada por uma tabela de hash
 * @param hash Tabela de hash a libertar
 */
void destroy_hashdatas(GHashTable* hash);

/* [Inserts functions] */

/**
 * @brief Insere uma struct business numa HashTable de businesses
 * @param bs HashTable de Businesses
 * @param b Struct Business a adicionar
 * @return TRUE caso seja a primeira inserção desse id, FALSE se for duplicado.
 */
int insert_business (BUSINESSES bs, BUSINESS b);
/**
 * @brief Insere uma struct reviews numa HashTable de reviews
 * @param rs HashTable de Reviews
 * @param r Struct reviews a adicionar
 * @return TRUE caso seja a primeira inserção desse id, FALSE se for duplicado.
 */
int insert_review (REVIEWS rs, REVIEW r);
/**
 * @brief Insere uma struct users numa HashTable de reviews
 * @param us HashTable de Users
 * @param u Struct users a adicionar
 * @return TRUE caso seja a primeira inserção desse id, FALSE se for duplicado.
 */
int insert_user (USERS us, USER u);

/**
 * @brief Insere um elemento numa tabela de hash
 * @param hash HashTable que vai receber o elemento
 * @param key Valor de hash
 * @param value Elemento a inserir
 */
void insert_hashdata(GHashTable * hash, gpointer key, gpointer value);


/* [Getters functions] */

/**
 * @brief Dado um business_id, devolve a struct business correspondente numa hashTable de businesses
 * @param bs HashTable de Businesses
 * @param business_id Business_id do business que queremos saber
 * @return BUSINESS Struct do business desejado
 */
BUSINESS get_business(BUSINESSES bs, char* business_id);
/**
 * @brief Dado um review_id, devolve a struct review correspondente numa hashTable de reviews
 * @param rs HashTable de Reviews
 * @param review_id Review_id da review que queremos saber
 * @return REVIEW Struct da review desejada
 */
REVIEW get_review(REVIEWS rs, char* review_id);
/**
 * @brief Dado um user_id, devolve a struct user correspondente numa hashTable de users
 * @param us HashTable de users
 * @param user_id User_id do user que queremos saber
 * @return USER Struct do user desejado
 */
USER get_user(USERS us, char* user_id);

/**
 * @brief Dado uma hashtable de businesses retorna o seu tamanho.
 * @param bs HashTable de businesses
 * @return int hash BUSINESSES size (Number of businesses)
 */
int get_businesses_size(BUSINESSES bs);

/**
 * @brief Dado uma hashtable de reviews retorna o seu tamanho.
 * @param bs HashTable de reviews
 * @return int hash REVIEWS size (Number of reviews)
 */
int get_reviews_size(REVIEWS rs);

/**
 * @brief Dado uma hashtable de users retorna o seu tamanho.
 * @param bs HashTable de users
 * @return int hash USERS size (Number of users)
 */
int get_users_size(USERS us);

/**
 * @brief Devolve o campo TABLE de uma hashdata
 * @param hd HashData que contém a TABLE pretendida
 * @return void* Devolve o apontador da TABLE pretendida
 */
void* get_hashdata_table (HASHDATA hd);

/**
 * @brief Devolve a "data" que está no indíce i do array de "data"
 * @param hd Hashdata que contém o array de "data"
 * @param i Indice do array de "data"
 * @return void* Apontador para "data"
 */
void* get_data (HASHDATA hd, int i);

/**
 * @brief Devolve um valor através de uma chave
 * @param hash HashTable onde se vai procurar o elemento
 * @param key Valor de hash
 * @return gpointer Elemento desejado
 */
gpointer get_hashdata(GHashTable * hash, gconstpointer key);

/**
 * @brief Insere um apontador de uma TABLE numa hashdata
 * @param hd HashData que vai receber um apontador novo para a TABLE
 * @param t Novo apontador da TABLE
 */
void put_hashdata_table (HASHDATA hd, void* t);

/**
 * @brief Insere um apontador para um certo dado na hashdata no indice i de um array de "data"
 * @param hd HashData que contém o array de "data"
 * @param i Indice do array de "data"
 * @param data Novo apontador para "data"
 */
void put_data (HASHDATA hd, int i, void* data);

/* ---------------//--------------- [Start of module hashes] ---------------//--------------- */

#endif
