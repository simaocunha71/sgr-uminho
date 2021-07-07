package model;

import java.util.Comparator;

/**
 * Classe que implementa um Comparator para UserReviewerComp
 */
public class UserReviewerComp implements Comparator<UserReviewer> {
    /**
     * Método que compara 2 UserReviewerComp
     * @param u1 UserReviewerComp u1
     * @param u2 UserReviewerComp u2
     * @return 0 se forem iguais, > 0 se u1 > u2; < 0 caso contrário
     */
    public int compare(UserReviewer u1, UserReviewer u2) {
        return u1.compareTo(u2);
    }
}
