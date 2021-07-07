package model;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * Classe que representa as estatisticas, que inclui os nomes dos últimos ficheiros lidos, o score das reviews atribuídas,
 * o número de users,reviews e businesses, um Set de business que foram avaliados, uma lista de listas de users que fizeram reviews e o número de reviews sem impacto
 */
public class Statistics implements Serializable {
    private String usersFile;
    private String businessesFile;
    private String reviewsFile;
    private ReviewScore[] reviews; //One -> reviewsAmount & Two -> reviewsScore
    private int usersAmount;
    private int businessesAmount;
    private int reviewsInvalidAmount;
    private Set<String> reviewedBusinesses;
    private List<Set<String>> usersReviewers;
    private int reviewsWithoutImpact;

    /**
     * Construtor vazio de Statistics
     */
    public Statistics(){
        this.usersFile = "";
        this.businessesFile = "";
        this.reviewsFile = "";
        this.usersAmount = 0;
        this.businessesAmount = 0;
        this.reviewsInvalidAmount = 0;
        this.reviewedBusinesses = new HashSet<>();
        this.reviews = new ReviewScore[12];
        this.usersReviewers = new ArrayList<>(12);
        for(int i = 0; i < 12; i++){
            this.reviews[i] = new ReviewScore();
            this.usersReviewers.add(i,new HashSet<>());
        }
        this.reviewsWithoutImpact = 0;
    }

    /**
     * Devolve o número de businesses
     * @return Número de businesses
     */
    public int getBusinessesAmount() {
        return businessesAmount;
    }

    /**
     * Altera o nome do ficheiro de business
     * @param businessesFile Novo nome
     */
    public void setBusinessesFile(String businessesFile) {
        this.businessesFile = businessesFile;
    }

    /**
     * Devolve o nome do ultimo ficheiro de business lido
     * @return Nome
     */
    public String getBusinessesFile() {
        return businessesFile;
    }

    /**
     * Altera o nome do ficheiro de users
     * @param usersFile Novo nome
     */
    public void setUsersFile(String usersFile) {
        this.usersFile = usersFile;
    }

    /**
     * Devolve o nome do ultimo ficheiro de users lido
     * @return Nome
     */
    public String getUsersFile() {
        return usersFile;
    }
    /**
     * Altera o nome do ficheiro de reviews
     * @param reviewsFile Novo nome
     */
    public void setReviewsFile(String reviewsFile) {
        this.reviewsFile = reviewsFile;
    }

    /**
     * Devolve o nome do ultimo ficheiro de reviews lido
     * @return Nome
     */
    public String getReviewsFile() {
        return reviewsFile;
    }

    /**
     * Devolve o número de reviews sem impacto
     * @return Número de reviews sem impacto
     */
    public int getReviewsWithoutImpact() {
        return reviewsWithoutImpact;
    }

    /**
     * Devolve o número de users
     * @return Número de users
     */
    public int getUsersAmount() {
        return usersAmount;
    }

    /**
     * Devolve o número de reviews de um dado mês
     * @param month Mês a procurar
     * @return Número de reviews desse mês
     */
    public int getReviewsAmount(int month) {
        return (month >= 1 && month <= 12) ? reviews[month-1].getReviewsAmount() : -1;
    }

    /**
     * Número de reviews num ano
     * @return Número de reviews num ano
     */
    public int getReviews() {
        int total = 0;
        for(int i = 0; i < 12; i++){
            total += this.reviews[i].getReviewsAmount();
        }
        return total;
    }

    /**
     * Devolve o score médio de reviews num mês
     * @param month Mês a procurar
     * @return Score médio
     */
    public double getReviewsAverageScore(int month) {
        return (month >= 1 && month <= 12) ? reviews[month-1].getAverageScore() : -1;
    }

    /**
     * Devolve o score médio de reviews
     * @return Score médio
     */
    public double getReviewsAverageScore() {
        double totalScore = 0;
        int totalReviews = 0;
        for(int i = 0; i < 12; i++){
            totalScore += this.reviews[i].getReviewsScore();
            totalReviews += this.reviews[i].getReviewsAmount();
        }
        return (totalReviews!=0) ? totalScore/totalReviews : 0;
    }

    /**
     * Adiciona um user que fez uma review
     * @param user Id do user
     * @param month Mês
     */
    public void addUserReviewer(String user, int month){
        if(month >= 1 && month <= 12)
            this.usersReviewers.get(month-1).add(user);
    }

    /**
     * Devolve o número de users que fizeram review
     * @return Número de users que fizeram review
     */
    public int getUsersReviewersAmount (){
        Set<String> usersReviewers = new HashSet<>();
        for(int i = 0; i < 12; i++){
            Set<String> usersReviewersMonth = this.usersReviewers.get(i);
            usersReviewers.addAll(usersReviewersMonth);
        }
        return usersReviewers.size();
    }
    /**
     * Devolve o número de users que fizeram review num mês
     * @param month Mês
     * @return Número de users que fizeram review nesse mês
     */
    public int getUsersReviewersAmount (int month){
        if(month >= 1 && month <= 12)
            return this.usersReviewers.get(month-1).size();
        else
            return -1;
    }

    /**
     * Adiciona uma review
     * @param r Review a adicionar
     */
    public void addReview(Review r){
        this.addReviewedBusiness(r.getBusinessId());
        this.addUserReviewer(r.getUserId(),r.getDate().getMonthValue());
        this.incReviewsWithoutImpact(r);
        this.incReviews(r.getDate().getMonthValue(),r.getStars());
    }

    /**
     * Devolve o número de reviews inválidas
     * @return Número de reviews inválidas
     */
    public int getReviewsInvalidAmount() {
        return reviewsInvalidAmount;
    }

    /**
     * Incrementa o número de reviews inválidas
     */
    public void incInvalidReviews (){
        this.reviewsInvalidAmount++;
    }

    /**
     * Incrementa o número de users
     */
    public void incUsers (){
        this.usersAmount++;
    }

    /**
     * Incrementa o número de business
     */
    public void incBusinesses(){
        this.businessesAmount++;
    }

    /**
     * Incrementa o número de reviews
     * @param month Mês
     * @param score Score
     */
    public void incReviews(int month, double score){
        if(month >= 1 && month <= 12 && score >= 0.0) {
            this.reviews[month - 1].incReviews();
            this.reviews[month - 1].incScore(score);
        }
    }

    /**
     * Incrementa o número de review sem impacto
     * @param r Review que poderá ser "sem impacto"
     */
    public void incReviewsWithoutImpact(Review r){
        if(r.getCool() + r.getFunny() + r.getUseful() == 0)
            this.reviewsWithoutImpact++;
    }

    /**
     * Adiciona um business que foi avaliado
     * @param id Id do business
     */
    public void addReviewedBusiness(String id){
        this.reviewedBusinesses.add(id);
    }

    /**
     * Devolve o número de businesses avaliados
     * @return Número de businesses avaliados
     */
    public int getReviewedBusinessesAmount(){
        return this.reviewedBusinesses.size();
    }

    /**
     * Devolve um set de business que foram avaliados
     * @return Set de business
     */
    public Set<String> getReviewedBusinesses(){
        return new HashSet<>(this.reviewedBusinesses);
    }

    /**
     * Verifica se um business foi avaliado
     * @param id Id do business
     * @return true se sim, false caso contrário
     */
    public boolean reviewedBusiness (String id){
        return this.reviewedBusinesses.contains(id);
    }


}
