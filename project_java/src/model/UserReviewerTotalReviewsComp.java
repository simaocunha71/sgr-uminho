package model;

import java.util.Comparator;

/**
 * Classe que implementa um Comparator para UserReviewer
 */
public class UserReviewerTotalReviewsComp implements Comparator<UserReviewer> {

    /**
     * Método que compara 2 UserReviewer
     * @param u1 UserReviewer 1
     * @param u2 UserReviewer 2
     * @return 0 se forem iguais, > 0 se u1 > u2; < 0 caso contrário
     */
    public int compare(UserReviewer u1, UserReviewer u2) {
        int c = u2.getReviewsAmount() - u1.getReviewsAmount();
        return (c!=0) ? c : u1.getId().compareTo(u2.getId());
    }
}