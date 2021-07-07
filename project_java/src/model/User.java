package model;

import java.io.Serializable;

/**
 * Classe representativa de um user, que inclui um id, o nome e uma string com os amigos do user
 */
public class User implements Serializable {
    private String id;
    private String name;
    private String friends;

    /**
     * Construtor vazio de um User
     */
    public User(){
        this.id = "";
        this.name = "";
        this.friends = "";
    }

    /**
     * Construtor parametrizado de um User
     * @param id Id de um user
     * @param name Nome do user
     * @param f String com os amigos do user
     */
    public User (String id, String name, String f){
        this.id = id;
        this.name = name;
        this.friends = f;
    }

    /**
     * Construtor de cópia de um User
     * @param u User
     */
    public User (User u){
        this.id = u.getId();
        this.name = u.getName();
        this.friends = u.getFriends();
    }

    /**
     * Construtor que, ao receber uma linha de um ficheiro e um booleano, efetua o parsing e cria o objeto user
     * @param s Linha do ficheiro
     * @param loadFriends Booleano que representa o ato de carregar os friends para o objeto user
     */
    public User (String s, boolean loadFriends) {
        this();
        String[] parameters = s.split(";");
        if (parameters.length == 3) {
            this.setId(parameters[0]);
            this.setName(parameters[1]);
            if (loadFriends)
                this.setFriends(parameters[2]);
        }
    }

    /**
     * Devolve o id de um user
     * @return Id de um user
     */
    public String getId() {
        return id;
    }

    /**
     * Altera o id de um user
     * @param id Novo id
     */
    public void setId(String id) {
        this.id = id;
    }

    /**
     * Devolve o nome de um user
     * @return Nome do user
     */
    public String getName() {
        return name;
    }

    /**
     * Altera o nome de um user
     * @param name Novo nome
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Devolve a string dos amigos de um user
     * @return String amigos
     */
    public String getFriends() {
        return friends;
    }

    /**
     * Altera os friends de um user
     * @param friends Novos friends
     */
    public void setFriends(String friends) {
        this.friends = friends;
    }

    /**
     * Método de cópia de um User
     * @return User
     */
    public User clone() {
        return new User(this);
    }

    /**
     * Verifica se 2 objetos User são iguais
     * @param o Objeto
     * @return true se sim, false caso contrário
     */
    public boolean equals(Object o) {
        if (o == this)
            return true;
        if (o == null || !o.getClass().equals(this.getClass()))
            return false;
        User u = (User) o;
        return this.id == u.id && 
               this.name.equals(u.name) &&
               this.friends.equals(u.friends);
    }

    /**
     * Devolve a string representativa de um user
     * @return String
     */
    public String toString() {
        StringBuilder sb = new StringBuilder("User {\n");
        sb.append("ID = '").append(id).append("'\n");
        sb.append("Nome = '").append(name).append("'\n");
        sb.append("Amigos: ").append(friends);
        sb.append("\n}");
        return sb.toString();
    }
}
