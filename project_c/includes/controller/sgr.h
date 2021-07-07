/**
 * @file sgr.h
 * @brief contém todas as funções responsáveis 
 * pelo acesso às diferentes tabelas de hash e pelas querys pedidas pela equipa docente;
 * @copyright Copyright (c) 2021
 */
#ifndef SGR_H
#define SGR_H

/* ---------------//--------------- [Start of module sgr] ---------------//--------------- */

/* ---------------//--------------- [Includes] ---------------//--------------- */
#include "../model/glibWarningAvoid.h"
#include "../model/reading.h"
#include "../controller/hashcontrol.h"

/* ---------------//--------------- [Defines] ---------------//--------------- */
/* [Typedefs] */

typedef struct sgr* SGR;

/* ---------------//--------------- [Functions] ---------------//--------------- */

/* [Initialization and destruction functions] */

/**
 * @brief Inicializa uma SGR (Sistema de Gestão de Recomendações)
 * @return SGR SGR inicializado
 */
SGR init_sgr ();

/**
 * @brief Liberta a memoria alocada para todos os campos do SGR
 * @param sgr SGR a libertar
 */
void free_sgr (SGR sgr);

/**
 * @brief [Query 1] Devolve o SGR, carregando os diferentes ficheiros para as diversas HashTables
 * @param users Ficheiro com os users
 * @param businesses Ficheiro com os businesses
 * @param reviews Ficheiro com as Reviews
 * @return SGR SGR carregada com os dados dos ficheiros
 */
SGR load_sgr(char *users, char *businesses, char *reviews);

/* [Boolean functions] */

/**
 * @brief Funçao booleana que diz se existe users.
 * @param SGR sgr
 * @return 1 se existir.
 */
int exist_users(SGR sgr);

/**
 * @brief Funçao booleana que diz se existe reviews.
 * @param SGR sgr
 * @return 1 se existir.
 */
int exist_reviews(SGR sgr);

/**
 * @brief Funçao booleana que diz se existe businesses.
 * @param SGR sgr
 * @return 1 se existir.
 */
int exist_businesses(SGR sgr);

/* [Queries] */

/**
 * @brief [Query 2] Determina a lista de business_names e o número total de businesses cujo nome inicia por uma dada letra. 
 * A procura é não case sensitive.
 * @param sgr SGR 
 * @param letter Letra inicial dos businesses a procurar
 * @return TABLE Table com business_names e total_number_business cujo nome começa por letter
 */
TABLE businesses_started_by_letter(SGR sgr, char letter);

/**
 * @brief [Query 3] Dado um id de negócio, determina a sua informação: nome, cidade, estado, stars,e número total reviews.
 * @param sgr SGR
 * @param business_id Business_id que se usa para procurar a respetiva informação de um business
 * @return TABLE Table com a informação pedida
 */
TABLE business_info(SGR sgr, char *business_id);

/**
 * @brief [Query 4] Dado um id de utilizador, determina a lista de negócios aos quais fez review. A informação associada a cada negócio deve ser o id e o nome.
 * @param sgr SGR
 * @param user_id User_id 
 * @return TABLE com a informaçao pedida
 */
TABLE businesses_reviewed(SGR sgr, char *user_id);

/**
 * @brief [Query 5] Dado um número n de stars e uma cidade, determina a lista de negócios com n ou mais stars na dada cidade.
 * A informação associada a cada negócio deve ser o seu id e nome.
 * @param sgr SGR
 * @param stars Stars de referencia
 * @param city cidade a procurar
 * @return TABLE Table com a informação pedida
 */
TABLE businesses_with_stars_and_city(SGR sgr, float stars, char *city);

/**
 * @brief [Query 6] Dado um número inteiro n, determinar a lista dos top n negócios (tendo em contao número médio de stars) 
 * em cada cidade.
 * A informação associada a cada negócio deve ser o seu id, nome, e número de estrelas.
 * @param sgr SGR
 * @param top Inteiro referente aos melhores top businesses
 * @return TABLE Table com a informação pedida
 */
TABLE top_businesses_by_city(SGR sgr, int top);

/**
 * @brief [Query 7] Determinar a lista de ids de utilizadores e o número total de utilizadores que tenham visitado 
 * mais de um estado , i.e. que tenham feito reviews em negócios de diferentes estados.
 * @param sgr SGR
 * @return TABLE Table com a informação pedida
 */
TABLE international_users(SGR sgr);

/**
 * @brief [Query 8] Dado um número inteiro n e uma categoria, determina a lista dos top n negócios (tendo em conta 
 * o número médio de stars) que pertencem a uma determinada categoria. 
 * A informação associada a cada negócio deve ser o seu id, nome, e número de estrelas
 * @param sgr SGR
 * @param top Inteiro referente aos melhores top businesses
 * @param category Categoria para filtrar os businesses
 * @return TABLE Table com a informação pedida
 */
TABLE top_businesses_with_category(SGR sgr, int top, char *category);

/**
 * @brief [Query 9] Dada uma palavra, determina a lista de ids de reviews que a referem no campo text.
 * @param sgr SGR
 * @param word Palavra a procurar
 * @return TABLE Table com a informação pedida
 */
TABLE reviews_with_word(SGR sgr, char *word);

/**
 * @brief [Query opcional] Dado um user id, coloca numa TABLE os amigos desse user.
 * @param sgr SGR
 * @param user_id User_id para filtrar a review 
 * @return TABLE Table com a informação pedida
 */
TABLE friends_of_user(SGR sgr, char *user_id);


/**
 * @brief [Query opcional] Dado um mode ('u','b' or 'r') coloca numa TABLE todos os id's (e os names) existentes. 
 * @param sgr SGR
 * @param mode Modo que diz qual catalogo o utilizador quer.
 * @return TABLE Table com o catalogo pedido.
 */
TABLE catalogues(SGR sgr, char mode);

/* ---------------//--------------- [End of module sgr] ---------------//--------------- */

#endif