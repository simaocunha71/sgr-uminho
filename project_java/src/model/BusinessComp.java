package model;

import java.util.Comparator;

/**
 * Classe que implementa um Comparator para Business
 */
public class BusinessComp implements Comparator<Business> {

    /**
     * Compara 2 business através da ordem alfabética não case sensitive.
     * @param b1 Business 1
     * @param b2 Business 2
     * @return 0 se são iguais; > 0 se b1 é maior do que b2; < 0 se b2 é maior do que b1
     */
    public int compare(Business b1, Business b2){
        return b1.getId().compareToIgnoreCase(b2.getId());
    }
}
