package model;

import java.util.Comparator;

/**
 * Classe que implementa um Comparator para a classe BusinessReviewsCount
 */
public class BusinessReviewedComp implements Comparator<BusinessReviewsCount> {
    /**
     * Compara 2 BusinessReviewsCount
     * @param b1 BusinessReviewsCount 1
     * @param b2 BusinessReviewsCount 2
     * @return 0 se forem iguais, > 0 se b1 for maior que b2, < 0 se b2 for maior que b1
     */
    public int compare(BusinessReviewsCount b1, BusinessReviewsCount b2) {
        return b1.compareTo(b2);
    }
}
