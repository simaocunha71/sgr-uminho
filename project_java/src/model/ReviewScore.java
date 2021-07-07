package model;

import java.io.Serializable;

/**
 * Classe que implementa a avalização a uma review
 */
public class ReviewScore implements Serializable {
    private int reviewsAmount;
    private double reviewsScore;

    /**
     * Construtor vazio de ReviewScore
     */
    public ReviewScore(){
        this.reviewsAmount = 0;
        this.reviewsScore = 0.0;
    }

    /**
     * Construtor parametrizado de ReviewScore
     * @param reviewsAmount Número de reviews
     * @param reviewsScore Score atribuído
     */
    public ReviewScore(int reviewsAmount, double reviewsScore){
        this.reviewsAmount = reviewsAmount;
        this.reviewsScore = reviewsScore;
    }

    /**
     * Incrementa o número de reviews
     */
    public void incReviews(){
        this.incReviews(1);
    }

    /**
     * Soma um valor ao número de reviews
     * @param one Valor a somar
     */
    public void incReviews(int one){
        this.reviewsAmount +=one;
    }

    /**
     * Incrementa o score atibuído
     */
    public void incScore(){
        this.incScore(1);
    }

    /**
     * Soma um valor ao score atribuído
     * @param two Valor a acrescentar
     */
    public void incScore(double two){
        this.reviewsScore +=two;
    }

    /**
     * Devolve o número de reviews
     * @return Número de reviews
     */
    public int getReviewsAmount() {
        return reviewsAmount;
    }

    /**
     * Devolve o score de reviews
     * @return Score
     */
    public double getReviewsScore() {
        return reviewsScore;
    }

    /**
     * Altera o número de reviews
     * @param reviewsAmount Novo valor
     */
    public void setReviewsAmount(int reviewsAmount) {
        this.reviewsAmount = reviewsAmount;
    }

    /**
     * Altera o score atribuído
     * @param reviewsScore Novo valor
     */
    public void setReviewsScore(int reviewsScore) {
        this.reviewsScore = reviewsScore;
    }

    /**
     * Devolve a pontuação média
     * @return Score médio
     */
    public double getAverageScore(){
        return (reviewsAmount!=0) ? (reviewsScore/reviewsAmount) : 0;
    }

    /**
     * Transforma uma ReviewScore em string
     * @return String representativa de ReviewScore
     */
    public String toString (){
        StringBuilder sb = new StringBuilder();
        sb.append("Total Reviews -> " + reviewsAmount).append("\n").append("Total score -> " + reviewsScore).append("\n");
        return sb.toString();
    }
}

