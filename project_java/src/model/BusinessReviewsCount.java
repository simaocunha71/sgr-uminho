package model;

/**
 * Classe que representa um business através do seu nome e id e o número total de reviews feitas a esse negócio
 */
public class BusinessReviewsCount {

    String businessId;
    String businessName;
    int totalReviews;

    /**
     * Construtor parametrizado de BusinessReviewsCount
     * @param businessId Id do business
     * @param businessName Nome do business
     */
    public BusinessReviewsCount(String businessId, String businessName){
        this.businessId = businessId;
        this.businessName = businessName;
        this.totalReviews = 0;
    }

    /**
     * Devolve o nome do business
     * @return Nome
     */
    public String getBusinessName(){
        return businessName;
    }

    /**
     * Devolve o total de reviews a esse business
     * @return Total de reviews
     */
    public int getTotalReviews() {
        return totalReviews;
    }

    /**
     * Devolve o id desse business
     * @return Id
     */
    public String getBusinessId() {
        return businessId;
    }

    /**
     * Incrementa o número de reviews desse business
     */
    public void addReview(){
        totalReviews++;
    }

    /**
     * Método que compara objetos BusinessReviewsCount
     * @param b2 BusinessReviewsCount
     * @return 0 se forem iguais, < 0 se b2 < objeto atual, > 1 caso contrário
     */
    public int compareTo(BusinessReviewsCount b2) {
        int c = b2.getTotalReviews() - this.getTotalReviews();
        return (c!=0) ? c : this.getBusinessName().compareToIgnoreCase(b2.getBusinessName());
    }

    /**
     * Transforma um BusinessReviewsCount em string
     * @return String representativa de BusinessReviewsCount
     */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("BusinessID -> "+ businessName +", TotalReviews -> "+totalReviews).append("\n");
        return sb.toString();
    }
}
