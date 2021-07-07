package model;

import java.util.HashSet;
import java.util.Set;

/**
 * Classe que representa um user que fez uma review
 */
public class UserReviewer extends User{

    ReviewScore reviews;
    Set<String> businessesReviewed;

    /**
     * Construtor vazio de UserReviewer
     */
    public UserReviewer(){
        this(new User());
    }

    /**
     * Construtor de UserReviewer que recebe um user
     * @param u User
     */
    public UserReviewer(User u){
        super(u);
        reviews = new ReviewScore(0,0);
        this.businessesReviewed = new HashSet<>();
    }

    /**
     * Devolve o score médio atribuído
     * @return Score médio
     */
    public double getAverageScore (){
        return reviews.getAverageScore();
    }

    /**
     * Adiciona uma review
     * @param r Review a adicionar
     */
    public void addReview (Review r){
        if(r.getUserId().equals(this.getId())){
            reviews.incReviews();
            reviews.incScore(r.getStars());
            businessesReviewed.add(r.getBusinessId());
        }
    }

    /**
     * Devolve o número de business avaliados pelo user
     * @return Número de business avaliados
     */
    public int businessReviewedAmount(){
        return (int) businessesReviewed.size();
    }

    /**
     * Devolve um set de todos os business avaliados pelo user
     * @return Set de business
     */
    public Set<String> getAllBusinessReviewed (){
        return new HashSet<>(businessesReviewed);
    }

    /**
     * Método que compara um UserReviewer
     * @param u2 UserReviewer
     * @return 0 se forem iguais, > 0 se u2 for menor que o objeto, < 0 caso contrário
     */
    public int compareTo(UserReviewer u2) {
        int c = (int) u2.businessReviewedAmount() - this.businessReviewedAmount();
        return (c!=0) ? c : this.getId().compareTo(u2.getId());
    }

    /**
     * Devolve o número de reviews feitas
     * @return Número de reviews feitas
     */
    public int getReviewsAmount(){
        return reviews.getReviewsAmount();
    }
}
