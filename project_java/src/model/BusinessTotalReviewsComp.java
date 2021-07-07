package model;

import java.util.Comparator;

/**
 * Classe que implementa um Comparator para BusinessReviewed
 */
public class BusinessTotalReviewsComp implements Comparator<BusinessReviewed> {
    /**
     * Compara 2 BusinessReviewed através do número de reviews feitas aos business respetivos. Se existir empate,
     * o critério passa a ser a ordem lexicográfica de id's
     * @param b1 BusinessReviewed 1
     * @param b2 BusinessReviewed 1
     * @return 0 se forem iguais, >0 se b1 > b2, <0 caso contrário
     */
    public int compare(BusinessReviewed b1, BusinessReviewed b2) {
        int c = b2.getReviewsAmount() - b1.getReviewsAmount();
        return (c!=0) ? c : b1.compareTo(b2);
    }
}
