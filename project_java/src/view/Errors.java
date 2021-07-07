package view;

/**
 * Classe de mensagens de erros
 */
public class Errors {

    public Errors(){}

    /**
     * Mensagem de erro de ficheiros inexistentes
     * @param filename Ficheiro 1
     * @param filename2 Ficheiro 2
     * @param filename3 Ficheiro 3
     */
    public void errorFiles (String filename, String filename2, String filename3){
        System.out.println("Algum dos ficheiros ("+filename+", "+filename2+" ou "+filename3+") não existe.");
    }

    /**
     * Mensagem de erro de ficheiro inexistente
     * @param filename Ficheiro
     */
    public void errorFile (String filename){
        System.out.println("O ficheiro "+filename+" não existe.");
    }

    /**
     * Mensagem de erro de ano inválido
     */
    public void errorYear (){
        System.out.println("Ano invalido");
    }

    /**
     * Mensagem de erro de mês inválido
     */
    public void errorMonth (){
        System.out.println("Mes invalido");
    }

    /**
     * Mensagem de erro de id de business inválido
     */
    public void errorBusinessId (){
        System.out.println("Business id inexistente");
    }

    /**
     * Mensagem de erro de id de user inválido
     */
    public void errorUserId (){
        System.out.println("User id inexistente");
    }

    /**
     * Mensagem de erro de página inválida
     */
    public void errorPage (){
        System.out.println("Página inválida");
    }
}
