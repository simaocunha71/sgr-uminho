package model.interfacesSGR;

import model.User;

import java.util.List;

/**
 * Interface para o catálogo de Users
 */
public interface UsersCatalog {
    /**
     * Devolve a lista de users para o catálogo
     * @return Lista de users
     */
    List<User> getUsersCatalog();
    /**
     * Devolve um user através do seu id
     * @param id Id do user
     * @return User
     */
    User getUser(String id);
    /**
     * Adiciona um user
     * @param u User a adicionar
     */
    void add(User u);
    /**
     * Valida um user
     * @param u User a validar
     * @return true se for válido, false caso contrário
     */
    boolean valid(User u);
}
