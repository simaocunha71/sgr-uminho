package model.interfacesSGR;

import model.*;

import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * Interface para as queries
 */
public interface Queries {
    /**
     * [QUERY 1]
     * Lista ordenada alfabeticamente com os identificadores dos negócios nunca avaliados e
     * o seu respetivo total
     * @return TreeSet dos business que não foram avaliados e o total
     */
    TreeSetBusinesses businessesNotReviewed();

    /**
     * [QUERY 2]
     * Dado um mês e um ano (válidos), determinar o número total global de reviews realizadas e
     * o número total de users distintos que as realizaram
     * @param month Mês
     * @param year Ano
     * @return Tuplo com o número total global de reviews realizadas e com o número total de users
     * distintos que as realizaram
     */
    PairInt allReviewsAndUsers(int month, int year);

    /**
     * [QUERY 3]
     * Dado um código de utilizador, determinar, para cada mês, quantas reviews fez,
     * quantos negócios distintos avaliou e que nota média atribuiu
     * @param userId Id do utilizador
     * @return UserReviewerPerMonth, que inclui quantas reviews um user efetuou,
     * quantos negócios distintos avaliou e que nota média atribuiu
     */
    UserReviewerPerMonth getUserReviewer (String userId);

    /**
     * [QUERY 4]
     * Dado o código de um negócio, determinar, mês a mês, quantas vezes foi avaliado,
     * por quantos users diferentes e a média de classificação
     * @param businessId Id do business
     * @return BusinessReviewed, que inclui quantas vezes um negoćio foi avaliado,
     * por quantos users diferentes e a média de classificação
     */
    BusinessReviewed allReviewsOfBusiness (String businessId);

    /**
     * [QUERY 5]
     * Dado o código de um utilizador determinar a lista de nomes de negócios que mais
     * avaliou (e quantos), ordenada por ordem decrescente de quantidade e, para
     *  quantidades iguais, por ordem alfabética dos negócios
     * @param userId Id do user
     * @return Lista dos nomes dos negócios que esse utilizador avaliou (e quantos)
     */
    Set<BusinessReviewsCount> businessesReviewedByUser (String userId);

    /**
     * [QUERY 6]
     * Determinar o conjunto dos X negócios mais avaliados (com mais reviews) em cada
     * ano, indicando o número total de distintos utilizadores que o avaliaram
     * (X é um inteiro dado pelo utilizador)
     * @param top Primeiros top negócios
     * @return Map de business com as avaliações de cada ano
     */
    Map<Integer, List<BusinessReviewed>> topBusinessesMostReviewedByYear (int top);


    /**
     * [QUERY 7]
     * Determinar, para cada cidade, a lista dos três mais famosos negócios em termos de número de reviews
     * @return Map de Business com as avaliações , onde a cada chave Cidade associa-se a lista dos
     * 3 mais famosos negócios
     */
    Map<String, List<BusinessReviewed>> topBusinessesMostReviewedByCity ();

    /**
     * [QUERY 8]
     * Determinar os códigos dos X utilizadores (sendo X dado pelo utilizador) que
     * avaliaram mais negócios diferentes, indicando quantos, sendo o critério de
     * ordenação a ordem decrescente do número de negócios
     * @param top Primeiros top utilizadores
     * @return Lista de utilizadores que avaliaram mais negócios diferentes
     */
    List<UserReviewer> topUsersReviewers (int top);


    /**
     * [QUERY 9]
     * Dado o código de um negócio, determinar o conjunto dos X users que mais o
     * avaliaram e, para cada um, qual o valor médio de classificação (ordenação cf. 5)
     * @param businessId Id de um business
     * @param top Primeiros top users
     * @return Lista de users que mais fizeram reviews e o valor médio de classificação
     */
    List<UserReviewer> topUsersReviewersByBusiness(String businessId, int top);


    /**
     * [QUERY 10]
     * Determinar para cada estado, cidade a cidade, a média de classificação de cada negócio
     * @return Map de negócios de todos os estados com a sua classificação média
     */
    BusinessesPerState allBusinessesPerState ();


}
