package model;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * Classe que representa um negócio: inclui o id do negócio, o nome, a cidade onde se localiza, o estado e uma lista de categorias onde se insere
 */
public class Business implements Serializable {
    private String id;
    private String name;
    private String city;
    private String state;
    private List<String> categories;

    /**
     * Construtor vazio da classe Business
     */
    public Business(){
        this.id = "";
        this.name = "";
        this.city = "";
        this.state = "";
        this.categories = new ArrayList<>();
    }

    /**
     * Construtor parametrizado da classe Business
     * @param id Id do business
     * @param name Nome do business
     * @param city Cidade do business
     * @param state Estado do business
     * @param clist Lista das categorias de um business
     */
    public Business(String id, String name, String city, String state, List<String> clist){
        this.id = id;
        this.name = name;
        this.city = city;
        this.state = state;
        this.categories = new ArrayList<>(clist);
    }

    /**
     * Construtor que, dado uma linha de um ficheiro, efetua o parse e cria um business
     * @param s Linha do ficheiro
     */
    public Business(String s) {
        this();
        if (s.split(";").length == 5) {
            this.setId(s.split(";")[0]);
            this.setName(s.split(";")[1]);
            this.setCity(s.split(";")[2]);
            this.setState(s.split(";")[3]);
            String aux = s.split(";")[4];
            String[] cat = aux.split(",");  
            for (String ss : cat){
                this.addCategory(ss);
            }
        }
    }

    /**
     * Construtor de cópia da classe Business
     * @param b Objeto original
     */
    public Business(Business b){
        this.id  = b.getId();
        this.name = b.getName();
        this.city = b.getCity();
        this.state = b.getState();
        this.categories = new ArrayList<>(b.getCategories());
    }

    /**
     * Devolve o id de um business
     * @return Id do business
     */
    public String getId() {
        return id;
    }

    /**
     * Altera o id de um business
     * @param id Novo id
     */
    public void setId(String id) {
        this.id = id;
    }

    /**
     * Devolve o nome de um business
     * @return Nome do business
     */
    public String getName() {
        return name;
    }

    /**
     * Altera o nome de um business
     * @param name Novo nome
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Devolve a cidade de um business
     * @return Cidade de um business
     */
    public String getCity() {
        return city;
    }

    /**
     * Altera a cidade de um business
     * @param city Nova cidade
     */
    public void setCity(String city) {
        this.city = city;
    }

    /**
     * Devolve o estado de um business
     * @return Estado de um business
     */
    public String getState() {
        return state;
    }

    /**
     * Altera o estado de um business
     * @param state Novo estado
     */
    public void setState(String state) {
        this.state = state;
    }

    /**
     * Devolve as categorias de um business
     * @return Categorias de um business
     */
    public List<String> getCategories() {
        return new ArrayList<>(this.categories);
    }

    /**
     * Adiciona uma categoria a uma lista de categorias de um business
     * @param c Categoria a adicionar
     */
    public void addCategory (String c){
        this.categories.add(c);
    }

    /**
     * Altera a lista das categorias de um business
     * @param clist Nova lista de categorias
     */
    public void setCategories(List<String> clist) {
        this.categories = new ArrayList<>(clist);
    }

    /**
     * Método de cópia de um business
     * @return Cópia de Business
     */
    public Business clone() {
        return new Business(this);
    }

    /**
     * Verifica se 2 objetos Business são iguais
     * @param o Objeto
     * @return true se são iguais, false caso contrário
     */
    public boolean equals(Object o) {
        if (o == this)
            return true;
        if (o == null || !o.getClass().equals(this.getClass()))
            return false;
        Business b = (Business) o;
        return this.id == b.id &&
               this.name == b.name &&
               this.city == b.city &&
               this.state == b.state &&
               this.categories.equals(b.categories);
    }

    /**
     * Transforma o objeto Business numa string
     * @return String representativa de um business
     */
    public String toString() {
        StringBuilder sb = new StringBuilder("Business {\n");
        sb.append("ID = '").append(id).append("'\n");
        sb.append("Nome = '").append(name).append("'\n");
        sb.append("Cidade = '").append(city).append("'\n");
        sb.append("Estado = '").append(state).append("'\n");
        sb.append("Categorias: ").append(categories.toString());
        sb.append("\n}");
        return sb.toString();
    }

}
