package model;

import java.util.ArrayList;
import java.util.List;

/**
 * Classe que representa as stars atribuídas por um utilizador ao longo do ano e uma lista com 12 listas constituídas pelos business avaliados em cada mês
 */
public class UserReviewerPerMonth extends User{
    ReviewScore [] reviews;
    List<List<String>> businessesReviewed;

    /**
     * Construtor vazio de UserReviewerPerMonth
     */
    public UserReviewerPerMonth (){
        this(new User());
    }

    /**
     * Construtor cópia de um UserReviewerPerMonth
     * @param u User
     */
    public UserReviewerPerMonth(User u) {
        super(u);
        this.reviews = new ReviewScore[12];
        this.businessesReviewed = new ArrayList<>(12);
        for(int i = 0; i < 12; i++){
            this.reviews[i] = new ReviewScore();
            this.businessesReviewed.add(i, new ArrayList<>());
        }
    }

    /**
     * Devolve as stars atribuídas num dado mês
     * @param month Mês a procurar
     * @return Stars atribuídas nesse mês
     */
    public double getAverageScore (int month){
        return (month >= 1 && month <= 12) ? reviews[month-1].getAverageScore() : -1;
    }

    /**
     * Devolve o número de reviews avaliadas num dado mês
     * @param month Mês a procurar
     * @return Número de reviews nesse mês
     */
    public int getReviewsAmount (int month){
        return (month >= 1 && month <= 12) ? reviews[month-1].getReviewsAmount() : -1;
    }

    /**
     * Devolve o valor médio de stars atribuídas ao longo do ano
     * @return Valor médio de stars ao longo do ano
     */
    public double getAverageScore (){
        double totalScore = 0;
        int totalReviews = 0;
        for(int i = 0; i < 12; i++){
            totalScore += reviews[i].getReviewsScore();
            totalReviews += reviews[i].getReviewsAmount();
        }
        return (totalReviews != 0) ? (totalScore/totalReviews) : 0;
    }

    /**
     * Adiciona uma review a UserReviewerPerMonth
     * @param r Review a adicionar
     */
    public void addReview (Review r){
        if(r.getUserId().equals(this.getId())){
            int month = r.getDate().getMonthValue();
            reviews[month-1].incReviews();
            reviews[month-1].incScore(r.getStars());
            businessesReviewed.get(month-1).add(r.getBusinessId());
        }
    }

    /**
     * Devolve o número de business avaliados num dado mês
     * @param month Mês a procurar
     * @return Número de business avaliados nesse mês
     */
    public int businessReviewedAmount(int month){
        return (int) businessesReviewed.get(month-1).stream().distinct().count();
    }

    /**
     * Devolve o número de business avaliados ao longo do ano
     * @return Número de business avaliados ao longo do ano
     */
    public int businessReviewedAmount(){
        long total = 0;
        for(int i = 0; i < 12; i++){
            total+=businessesReviewed.get(i).stream().distinct().count();
        }

        return (int) total;
    }

    /**
     * Devolve a lista de todos os business avaliados ao longo do ano
     * @return Lista de todos os busienss avaliados ao longo do ano
     */
    public List<String> getAllBusinessReviewed (){
        List<String> result = new ArrayList<>();
        for(int i = 0; i<12; i++){
            result.addAll(businessesReviewed.get(i));
        }
        return result;
    }

    /**
     * Transforma o objeto UserReviewerPerMonth numa string
     * @return String representativa de UserReviewerPerMonth
     */
    public String toString (){
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < 12; i++){
            sb.append("Mês "+(i+1)+ ": reviews-> "+reviews[i].getReviewsAmount() + ", score-> "+reviews[i].getReviewsScore() +
                    ", Negocios -> " + businessesReviewed.get(i).toString()).append("\n");
        }
        return sb.toString();
    }
}
