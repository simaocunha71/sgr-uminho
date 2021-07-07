package model;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * Classe que representa um negócio pelo seu id, as stars atribuídas ao longo do ano e uma lista de 12 listas dos users que avaliaram o negócio por mês
 */
public class BusinessReviewed {
    ReviewScore [] reviews;
    List<Set<String>> usersReviewers;
    String id;

    /**
     * Construtor que inicializa uma BusinessReviewed
     * @param id Id de um business
     */
    public BusinessReviewed(String id){
        this.id = id;
        this.reviews = new ReviewScore[12];
        this.usersReviewers = new ArrayList<>(12);
        for(int i = 0; i < 12; i++){
            this.reviews[i] = new ReviewScore(0,0);
            this.usersReviewers.add(i,new HashSet<>());
        }
    }

    /**
     * Devolve o id de um business
     * @return Id do business
     */
    public String getId() {
        return id;
    }

    /**
     * Adiciona uma review a BusinessReviewsCount
     * @param r Review a adicionar
     */
    public void addReview(Review r){
        int month = r.getDate().getMonthValue();
        double score = r.getStars();
        String userId = r.getUserId();
        this.reviews[month-1].incReviews();
        this.reviews[month-1].incScore(score);
        this.usersReviewers.get(month-1).add(userId);
    }

    /**
     * Devolve o número de reviews num dado mês
     * @param month Mês a procurar
     * @return Número de reviews nesse mês
     */
    public int getReviewsAmount(int month) {
        return this.reviews[month-1].getReviewsAmount();
    }

    /**
     * Devolve o número de reviews atribuídas ao longo do ano
     * @return Número de reviews atribuídas ao longo do ano
     */
    public int getReviewsAmount() {
        int total = 0;
        for(int i = 0; i < 12; i++){
            total += this.reviews[i].getReviewsAmount();
        }
        return total;
    }

    /**
     * Devolve o número de users que avaliaram esse negócio num dado mês
     * @param month Mês a procurar
     * @return Número de Users que avaliaram esse negócio nesse mês
     */
    public int getUsersReviewersAmount(int month){
        return usersReviewers.get(month-1).size();
    }

    /**
     * Devolve o número de users que avaliaram esse negócio ao longo do ano
     * @return Número de users que avaliaram esse negócio ao longo do ano
     */
    public int getUsersReviewersAmount(){
        Set <String> totalUsers = new HashSet<>();
        for(int i = 0; i<12; i++){
            totalUsers.addAll(usersReviewers.get(i));
        }
        return totalUsers.size();
    }

    /**
     * Devolve as stars atribuídas num dado mês
     * @param month Mês a procurar
     * @return Stars atribuídas num dado mês
     */
    public double getAverageScore(int month) {
        return (month >= 1 && month <= 12) ? reviews[month-1].getAverageScore() : -1;
    }

    /**
     * Devolve as stars atribuídas ao longo do ano
     * @return Stars atribuídas ao longo do ano
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
     * Método que compara um BusinessReviewed, cujo critério é a ordem lexicográfica do id de um negócio
     * @param b Négocio
     * @return 0 se forem iguais, > 0 se b for menor ao objeto atual, < 0 caso contrário
     */
    public int compareTo(BusinessReviewed b) {
        return this.getId().compareTo(b.getId());
    }

    /**
     * Tranforma o objeto BusinessReviewed em string
     * @return String representativa de BusinessReviewed
     */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < 12; i++){
            sb.append("reviews-> "+reviews[i].getReviewsAmount() + ", score-> "+reviews[i].getReviewsScore() + ", Users -> " + usersReviewers.get(i).size()).append("\n");
        }
        return sb.toString();
    }
}
