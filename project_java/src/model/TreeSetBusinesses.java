package model;

import java.util.*;

/**
 * Classe que representa um TreeSet de Business
 */
public class TreeSetBusinesses {
    Set<Business> businesses;
    int total;

    /**
     * Construtor de um TreeSet de business que recebe um comparator
     * @param comp Comparator cujo critério de ordenação é a ordem lexicográfica dos nomes dos business
     */
    public TreeSetBusinesses(Comparator<Business> comp){
        this.businesses = new TreeSet<>(comp);
        this.total = 0;
    }

    /**
     * Adiciona um business ao Set de Businesses
     * @param b Business a adicionar
     */
    public void add(Business b){
        this.businesses.add(b.clone());
        this.total++;
    }

    /**
     * Devolve uma lista dos id's dos business que não receberam review
     * @return Lista dos id's
     */
    public List<String> getBusinessesNotReviewedId() {
        List<String> r = new ArrayList<>();
        businesses.forEach(b -> r.add(b.getId()));
        return r;
    }

    /**
     * Devolve uma lista dos nomes dos business que não receberam review
     * @return Lista dos nomes
     */
    public List<String> getBusinessesNotReviewedName() {
        List<String> r = new ArrayList<>();
        businesses.forEach(b -> r.add(b.getName()));
        return r;
    }

    /**
     * Devolve o total de businesses num Set
     * @return Total de businesses num Set
     */
    public int getTotal(){
        return this.total;
    }
}
