package model;

/**
 * Classe que representa um tuplo com o número total de reviews e com utilizadores únicos
 */
public class PairInt {
    private int one;
    private int two;

    /**
     * Construtor vazio de PairInt
     */
    public PairInt(){
        this.one = 0;
        this.two = 0;
    }

    /**
     * Construtor parametrizado de um PairInt
     * @param one Lado esquerdo do tuplo
     * @param two Lado direito do tuplo
     */
    public PairInt(int one, int two){
        this.one = one;
        this.two = two;
    }

    /**
     * Incrementa o lado esquerdo de um tuplo
     */
    public void incOne(){
        this.incOne(1);
    }

    /**
     * Soma um valor ao lado esquerdo de um tuplo
     * @param one Valor a adicionar
     */
    public void incOne(int one){
        this.one+=one;
    }

    /**
     * Incrementa o lado direito de um tuplo
     */
    public void incTwo(){
        this.incTwo(1);
    }

    /**
     * Soma um valor ao lado direito de um tuplo
     * @param two Valor a adicionar
     */
    public void incTwo(int two){
        this.two+=two;
    }

    /**
     * Devolve o lado esquerdo de um tuplo
     * @return Valor do lado esquerdo de um tuplo
     */
    public int getOne() {
        return one;
    }
    /**
     * Devolve o lado direito de um tuplo
     * @return Valor do lado direito de um tuplo
     */
    public int getTwo() {
        return two;
    }

    /**
     * Transforma um tuplo em string
     * @return String
     */
    public String toString (){
        StringBuilder sb = new StringBuilder();
        sb.append("Total Reviews -> " + one).append("\n").append("Unique users -> " + two).append("\n");
        return sb.toString();
    }
}

