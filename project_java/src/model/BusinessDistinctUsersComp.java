package model;

import java.util.Comparator;

/**
 * Classe que implementa um Comparator para BusinessReviewed
 */
public class BusinessDistinctUsersComp implements Comparator<BusinessReviewed> {
    /**
     * Compara 2 business através do número de utilizadores que a avaliaram. Se existir empate, o critério passa a ser
     * a ordem lexicogŕafica do id
     * @param b1 BusinessReviewed 1
     * @param b2 BusinessReviewed 2
     * @return 0 se forem iguais, > 0 se b1 > b2, < 0 de b1 < b2
     */
    public int compare(BusinessReviewed b1, BusinessReviewed b2) {
        int c = b2.getUsersReviewersAmount() - b1.getUsersReviewersAmount();
        return (c!=0) ? c : b1.compareTo(b2);
    }
}
