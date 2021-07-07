package view;

import java.time.LocalDate;

/**
 * Classe de mensagens
 */
public class Messages {
    public Messages(){}

    /**
     * Imprime pergunta pelo mês
     */
    public void askMonth(){
        System.out.print("Escreve um mes [1-12]: ");
    }

    /**
     * Imprime pergunta pelo ano
     */
    public void askYear(){
        System.out.print("Escreve um ano [2000-"+LocalDate.now().getYear()+"]: ");
    }

    /**
     * Imprime pergunta pelo top
     */
    public void askTop(){
        System.out.print("Qual o top?: ");
    }

    /**
     * Imprime pergunta pelo id do business
     */
    public void askBusinessId(){
        System.out.print("Escreve um business id: ");
    }

    /**
     * Imprime pergunta pelo id do user
     */
    public void askUserId(){
        System.out.print("Escreve um user id: ");
    }

    /**
     * Imprime pergunta pelo ficheiro
     * @param file Nome do ficheiro
     */
    public void askFile(String file){
        System.out.print("Escreve o nome do ficheiro das \""+file+"\": ");
    }

    /**
     * Imprime pergunta pelo objeto
     */
    public void askObject(){
        System.out.print("Escreve o nome do ficheiro objeto: ");
    }

    /**
     * Imprime mensagem de carregamento de ficheiros
     */
    public void loadingFiles(){
        System.out.println("Carregando os ficheiros.");
    }

    /**
     * Imprime mensagem de carregamento de objeto
     * @param objectFile Nome do objeto
     */
    public void loadingObject(String objectFile){
        System.out.println("Carregando o ficheiro objeto "+objectFile);
    }

    /**
     * Imprime mensagem de gravação de objeto
     * @param file Nome do objeto
     */
    public void savingObject(String file){
        System.out.println("Salvando em "+file);
    }

    /**
     * Imprime mensagem de gravação concluída
     */
    public void savingFinish(){
        System.out.println("Ficheiro objeto salvo.");
    }

    /**
     * Imprime mensagem de carregamento concluido
     * @param time Tempo de carregamento
     */
    public void loadingFinish(double time){
        System.out.println("Carregamento concluído em "+String.format("%.3f", time)+" ms.");
    }
}
