package model.interfacesSGR;

import model.Review;

import java.util.List;

/**
 * Interface para o catálogo de reviews
 */
public interface ReviewsCatalog {
    /**
     * Devolve a lista de reviews para o catálogo
     * @return Lista de reviews
     */
    List<Review> getReviewsCatalog();

    /**
     * Devolve uma review através do seu id
     * @param id Id da review
     * @return Review
     */
    Review getReview(String id);
    /**
     * Adiciona uma review
     * @param r Review a adicionar
     */
    void add(Review r);

    /**
     * Valida uma review
     * @param r Review a validar
     * @return true se for válido, false caso contrário
     */
    boolean valid(Review r);
}