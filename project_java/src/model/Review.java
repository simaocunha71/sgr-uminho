package model;

import java.io.Serializable;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;

/**
 * Classe que representa uma review, que inclui o id da review, o id do utilizador que efetuou a review,
 * o id do business que obteve a review, as stars atribuídas, o número de pessoas que a acharam úteis,
 * o número de pessoas que a acharam engraçada, o número de pessoas que a acharam "cool",
 * a data em que a crítica foi efetuada e o comentário à review
 */
public class Review implements Serializable {
    private String id;
    private String userId;
    private String businessId;
    private double stars;
    private int useful;
    private int funny;
    private int cool;
    private LocalDateTime date;
    private String text;

    /**
     * Construtor vazio de uma review
     */
    public Review (){
        this.id = "";
        this.userId = "";
        this.businessId = "";
        this.stars = -1;
        this.useful = -1;
        this.funny = -1;
        this.cool = -1;
        this.date = null;
        this.text = "";
    }

    /**
     * Construtor que recebe uma string de um ficheiro, efetua o parsing e cria um objeto Review
     * @param s Linha de um ficheiro
     */
    public Review (String s) {
        this();
        String[] parameters = s.split(";", -1);
        if (parameters.length >= 9) {
            this.setId(parameters[0]);
            this.setUserId(parameters[1]);
            this.setBusinessId(parameters[2]);
            try{
                this.setStars(Double.parseDouble(parameters[3]));}
            catch (NumberFormatException e){
                this.setStars(-1);
            }
            try{
                this.setUseful(Integer.parseInt(parameters[4]));
            }
            catch (NumberFormatException e){
                this.setUseful(-1);
            }
            try{
                this.setFunny(Integer.parseInt(parameters[5]));
            }
            catch (NumberFormatException e){
                this.setFunny(-1);
            }
            try{
                this.setCool(Integer.parseInt(parameters[6]));
            }
            catch (NumberFormatException e){
                this.setCool(-1);
            }
            this.setDate(this.stringToLocalDateTime(parameters[7]));
            this.setText(parameters[8]);
        }
    }

    /**
     * Construtor parametrizado de uma review
     * @param id Id da review
     * @param userId Id do utilizador
     * @param businessId Id do negócio
     * @param stars Stars atribuídas
     * @param useful Número de pessoas que a acharam úteis
     * @param funny Número de pessoas que a acharam engraçada
     * @param cool Número de pessoas que a acharam "cool"
     * @param date Data em que a review foi executada
     * @param text Comentário à review
     */
    public Review(String id, String userId, String businessId, int stars,
                  int useful, int funny, int cool, LocalDateTime date, String text){
        this.id = id;
        this.userId = userId;
        this.businessId = businessId;
        this.stars = stars;
        this.useful = useful;
        this.funny = funny;
        this.cool = cool;
        this.date = date;
        this.text = text;     
    }

    /**
     * Construtor de cópia de Review
     * @param r Objeto original
     */
    public Review (Review r){
        this.id = r.getId();
        this.userId = r.getUserId();
        this.businessId = r.getBusinessId();
        this.stars = r.getStars();
        this.useful = r.getUseful();
        this.funny = r.getFunny();
        this.cool = r.getCool();
        this.date = r.getDate();
        this.text = r.getText();
    }

    /**
     * Devolve o id de uma review
     * @return Id da review
     */
    public String getId() {
        return id;
    }

    /**
     * Altera o id de uma review
     * @param id Novo id
     */
    public void setId(String id) {
        this.id = id;
    }

    /**
     * Devolve o id do utilizador que fez a review
     * @return Id do utilizador
     */
    public String getUserId() {
        return userId;
    }

    /**
     * Altera o id do utilizador que fez a review
     * @param userId Novo id
     */
    public void setUserId(String userId) {
        this.userId = userId;
    }

    /**
     * Devolve o id do business que recebeu a review
     * @return Id do business
     */
    public String getBusinessId() {
        return businessId;
    }

    /**
     * Altera o id do business de uma review
     * @param businessId Novo id
     */
    public void setBusinessId(String businessId) {
        this.businessId = businessId;
    }

    /**
     * Devolve as stars atribuídas a uma review
     * @return Stars atribuídas
     */
    public double getStars() {
        return stars;
    }

    /**
     * Altera as stars atribuídas a uma review
     * @param stars Novas stars
     */
    public void setStars(double stars) {
        this.stars = stars;
    }

    /**
     * Devolve o número de pessoas que acharam a review útil
     * @return Número de pessoas que acharam a review útil
     */
    public Integer getUseful() {
        return useful;
    }

    /**
     * Altera o valor do número de pessoas que acharam a review útil
     * @param useful Novo valor
     */
    public void setUseful(Integer useful) {
        this.useful = useful;
    }

    /**
     * Altera o valor do número de pessoas que acharam a review engraçada
     * @param funny Novo valor
     */
    public void setFunny(Integer funny) {
        this.funny = funny;
    }

    /**
     * Devolve o valor do número de pessoas que acharam a review engraçada
     * @return Número de pessoas que acharam a review engraçada
     */
    public Integer getFunny() {
        return funny;
    }

    /**
     * Altera o valor do número de pessoas que acharam a review "cool"
     * @param cool Novo valor
     */
    public void setCool(Integer cool) {
        this.cool = cool;
    }

    /**
     * Devolve o valor do número de pessoas que acharam a review "cool"
     * @return Número de pessoas que acharam a review "cool"
     */
    public Integer getCool() {
        return cool;
    }

    /**
     * Altera a data de uma review
     * @param date Nova data
     */
    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    /**
     * Devolve a data de uma review
     * @return Data da review
     */
    public LocalDateTime getDate() {
        return date;
    }

    /**
     * Altera o comentário de uma review
     * @param text Novo comentário
     */
    public void setText(String text) {
        this.text = text;
    }

    /**
     * Devolve o comentário de uma review
     * @return Comentário da review
     */
    public String getText() {
        return text;
    }

    /**
     * Método de cópia de uma review
     * @return Cópia de review
     */
    public Review clone() {
        return new Review(this);
    }

    /**
     * Verifica se 2 objetos Review são iguais
     * @param o Objeto
     * @return true se sim, false caso contrário
     */
    public boolean equals(Object o) {
        if (o == this)
            return true;
        if (o == null || !o.getClass().equals(this.getClass()))
            return false;
        Review r = (Review) o;
        return this.id.equals(r.id) &&
               this.businessId.equals(r.businessId) &&
               this.userId.equals(r.userId) &&
               this.stars == r.stars &&
               this.useful == r.useful &&
               this.funny == r.funny &&
               this.cool == r.cool &&
               this.date.equals(r.date) &&
               this.text.equals(r.text);
    }

    /**
     * Transforma o objeto Review em string
     * @return String representativa de uma review
     */
    public String toString() {
        StringBuilder sb = new StringBuilder("Review {\n");
        sb.append("ID = '").append(id).append("'\n");
        sb.append("BusinessID = '").append(businessId).append("'\n");
        sb.append("UserID = '").append(userId).append("'\n");
        sb.append("Stars : '").append(stars).append("'\n");
        sb.append("Useful: ").append(useful).append("'\n");
        sb.append("Funny: ").append(funny).append("'\n");
        sb.append("Cool: ").append(cool).append("'\n");
        sb.append("Date: ").append(date).append("'\n");;
        sb.append("Text: ").append(text).append("'\n");
        sb.append("\n}");
        return sb.toString();
    }

    /**
     * Transforma uma string em LocalDateTime
     * @param s String data
     * @return LocalDateTime criada
     */
    public LocalDateTime stringToLocalDateTime (String s){
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        try {
            return LocalDateTime.parse(s, formatter);
        }catch (DateTimeParseException e){
            return null;
        }
    }


}
