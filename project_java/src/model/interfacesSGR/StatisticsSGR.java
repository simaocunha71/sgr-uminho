package model.interfacesSGR;

/**
 * Interface para as estatísticas
 */
public interface StatisticsSGR {
    /**
     * Devolve o número de users
     * @return Número de Users
     */
    int usersAmount ();
    /**
     * Devolve o número de businesses
     * @return Número de businesses
     */
    int businessesAmount();
    /**
     * Devolve o número de reviews
     * @return Número de reviews
     */
    int reviewsAmount();

    /**
     * Devolve o número de reviews de um mês
     * @param month Mês a procurar
     * @return Número de reviews
     */
    int reviewsAmount(int month);

    /**
     * Número de reviews inválidas
     * @return Número de reviews inválidas
     */
    int invalidReviewsAmount();

    /**
     * Número de businesses que foram avaliados
     * @return Número de businesses que foram avaliados
     */
    int reviewedBusinessesAmount();

    /**
     * Número de businesses que não foram avaliados
     * @return Número de businesses que não foram avaliados
     */
    int notReviewedBusinessesAmount();

    /**
     * Número de users que fizeram reviews
     * @return Número de users que fizeram reviews
     */
    int usersReviewersAmount();

    /**
     * Número de users que fizeram reviews num dado mês
     * @param month Mês a procurar
     * @return Número de users que fizeram reviews nesse mês
     */
    int usersReviewersAmount(int month);

    /**
     * Número de users que não fizeram reviews
     * @return Número de users que não fizeram reviews
     */
    int notUsersReviewersAmount();

    /**
     * Número de reviews sem impacto
     * @return Número de reviews sem impacto
     */
    int reviewsWithoutImpactAmount();

    /**
     * Média das avaliações num dado mês
     * @param month Mês a procurar
     * @return Média das avaliações num dado mês
     */
    double averageReviewsScore(int month);
    /**
     * Média das avaliações
     * @return Média das avaliações
     */
    double averageReviewsScore();

    /**
     * Devolve a string do último ficheiro de users lido
     * @return String do último ficheiro de users lido
     */
    String lastUsersFileRead();
    /**
     * Devolve a string do último ficheiro de reviews lido
     * @return String do último ficheiro de reviews lido
     */
    String lastReviewsFileRead();
    /**
     * Devolve a string do último ficheiro de business lido
     * @return String do último ficheiro de business lido
     */
    String lastBusinessesFileRead();

}
