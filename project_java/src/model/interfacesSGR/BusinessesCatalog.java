package model.interfacesSGR;

import model.Business;

import java.util.List;

/**
 * Interface para o catálogo de business
 */
public interface BusinessesCatalog {
    /**
     * Devolve a lista de business para o catálogo
     * @return Lista de business
     */
    List<Business> getBusinessesCatalog();

    /**
     * Devolve um business através do seu id
     * @param id Id do business
     * @return Business
     */
    Business getBusiness(String id);

    /**
     * Adiciona um business
     * @param u Business a adicionar
     */
    void add(Business u);

    /**
     * Valida um business
     * @param u Business a validar
     * @return true se for válido, false caso contrário
     */
    boolean valid(Business u);
}