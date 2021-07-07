package model.interfacesSGR;

import java.io.IOException;

/**
 * Interface de leitura de dados de ficheiros
 */
public interface ReadingSGR {
    /**
     * Incorpora as leituras dos 3 tipos de ficheiros
     * @param businessesFile Nome do ficheiro dos businesses
     * @param usersFile Nome do ficheiro dos users
     * @param reviewsFile Nome do ficheiro das reviews
     * @param loadFriends Booleano que indica se é carregada ou não os amigos de um user
     * @throws IOException Exceção que é lançada caso não detete o nome do ficheiro
     */
    void readSGR(String businessesFile, String usersFile, String reviewsFile, boolean loadFriends) throws IOException;

    /**
     * Lê um ficheiro de business e armazena-o em memória.
     * @param businessFile Nome do ficheiro de business
     * @throws IOException Exceção que é lançada caso não detete o nome do ficheiro
     */
    void readBusinesses(String businessFile) throws IOException;

    /**
     * Lê um ficheiro de users e armazena-o em memória.
     * @param usersFile Nome do ficheiro de users
     * @param loadFriends Booleano que indica se é carregada ou não os amigos de um user
     * @throws IOException Exceção que é lançada caso não detete o nome do ficheiro
     */
    void readUsers(String usersFile, boolean loadFriends) throws IOException;

    /**
     * Lê um ficheiro de reviews e armazena-o em memória.
     * @param reviewsFile Nome do ficheiro de reviews
     * @throws IOException Exceção que é lançada caso não detete o nome do ficheiro
     */
    void readReviews(String reviewsFile) throws IOException;
}
