package view;

import java.text.DateFormatSymbols;
import java.util.ArrayList;
import java.util.List;

/**
 * Classe de view das queries
 */
public class ViewQueries implements ANSIIColour{

    public ViewQueries(){}

    /**
     * Imprime tempo de execução
     * @param time Tempo de execução
     */
    public void executionTime (double time){
        System.out.println("tempo de execuçao: "+String.format("%.3f", time)+" ms");
    }

    /**
     * View para query
     * @param colunes Colunas
     * @param lines Linhas
     * @param page Pagina atual
     * @param pages Paginas
     * @param nameSize Nome
     * @param size Tamanho
     */
    public void viewQuery(List<String> colunes, List<List<String>> lines, int page, int pages, String nameSize, int size){
        int nC = colunes.size();
        int nL = lines.size();
        int [] tamC = new int [nC];
        int total = 1;
        for(int i = 0; i < nC; i++){
            tamC[i] = colunes.get(i).length();
            for (List<String> line : lines) {
                if (line.get(i).length() > tamC[i])
                    tamC[i] = line.get(i).length();
            }
            tamC[i] += 2;
            total += tamC[i] + 1;
        }

        StringBuilder sb = new StringBuilder();
        sb.append(lineDash(total)).append(line(colunes,tamC)).append(lineDash(total));
        int finalTotal = total;
        lines.forEach(l -> sb.append(line(l,tamC)).append(lineDash(finalTotal)));
        if(!nameSize.equals("")) sb.append(nameSize).append(": ").append(size).append("\n");
        if(pages>1) {
            sb.append("Pagina ").append(page).append("/").append(pages).append("\n");
            sb.append("v -> Voltar ").append("| s -> Seguinte | a -> Anterior : ");
        }
        else sb.append("v -> Voltar : ");
        System.out.print(sb.toString());
    }

    /**
     * Linha da página
     * @param line Linha
     * @param tamC Array
     * @return Linha da página
     */
    private String line(List<String> line, int [] tamC){
        StringBuilder sb = new StringBuilder();
        int nC = line.size();
        sb.append("|");
        for(int i = 0; i < nC; i++){
            String s = line.get(i);
            int tamS = s.length();
            int spaces = (tamC[i] - tamS)/2;
            sb.append(" ".repeat(spaces)).append(s);
            if((tamC[i] - tamS) % 2 != 0)
                spaces++;
            sb.append(" ".repeat(spaces)).append("|");
        }
        sb.append("\n");
        return sb.toString();
    }

    /**
     * Imprime "-" tam vezes
     * @param tam Inteiro
     * @return String
     */
    private String lineDash(int tam){
        return "-".repeat(tam)+"\n";
    }

    /**
     * View do help das queries
     */
    public void help(){
        System.out.println("************************************** Manual das queries **************************************");
        System.out.println(ANSI_YELLOW+" 1."+ ANSI_RESET + ANSI_CYAN+ " Lista ordenada alfabeticamente"+ANSI_RESET+" com os"+ANSI_GREEN+
                " identificadores dos negócios nunca avaliados"+ANSI_RESET+" e o seu"+ANSI_GREEN+" respetivo total"+ANSI_RESET);
        System.out.println(ANSI_YELLOW+" 2."+ ANSI_RESET +" Dado um "+ANSI_GREEN+"mês"+ ANSI_RESET +" e um "+ANSI_GREEN+"ano"+ ANSI_RESET +
                " (válidos), determinar o "+ ANSI_CYAN+"número total global de reviews realizadas"+ANSI_RESET+" e o "+ ANSI_CYAN+"número total de users distintos que as realizaram"+ANSI_RESET+".");
        System.out.println(ANSI_YELLOW+" 3."+ ANSI_RESET +" Dado um "+ANSI_GREEN+"código de utilizador"+ ANSI_RESET +
                ", determinar, para cada mês, "+ANSI_CYAN+"quantas reviews fez"+ANSI_RESET+", "+ANSI_CYAN+"quantos negócios distintos avaliou "+ANSI_RESET+
                "e que "+ANSI_CYAN+"nota média atribuiu"+ANSI_RESET+".");
        System.out.println(ANSI_YELLOW+" 4."+ ANSI_RESET +" Dado o "+ANSI_GREEN+"código de um negócio"+ ANSI_RESET +
                ", determinar, mês a mês, "+ ANSI_CYAN+"quantas vezes foi avaliado"+ ANSI_RESET +", "+ ANSI_CYAN+"por quantos users diferentes"+ ANSI_RESET +
                " e a "+ ANSI_CYAN+"média de classificação"+ ANSI_RESET +".");
        System.out.println(ANSI_YELLOW+" 5."+ ANSI_RESET +" Dado o "+ ANSI_GREEN+"código de um utilizador"+ANSI_RESET+
                " determinar a "+ANSI_CYAN+"lista de nomes de negócios que mais avaliou (e quantos)"+ANSI_RESET+", ordenada por ordem "+ANSI_CYAN+"decrescente"+
                ANSI_RESET+" de quantidade e, para quantidades iguais, por ordem "+ANSI_CYAN+"alfabética"+ANSI_RESET+" dos negócios;");
        System.out.println(ANSI_YELLOW+" 6."+ ANSI_RESET +" Determinar o conjunto dos "+ ANSI_GREEN+"X"+ANSI_CYAN+
                " negócios mais avaliados (com mais reviews) em cada ano"+ANSI_RESET+", indicando o "+ANSI_CYAN+"número total de distintos utilizadores que o avaliaram"+
                ANSI_RESET+" (X é dado pelo utilizador);");
        System.out.println(ANSI_YELLOW+" 7."+ ANSI_RESET +" Determinar, "+ ANSI_GREEN+"para cada cidade"+ANSI_RESET+
                ", a "+ANSI_CYAN+"lista dos três mais famosos negócios em termos de número de reviews"+ANSI_RESET+".");
        System.out.println(ANSI_YELLOW+" 8."+ ANSI_RESET +" Determinar os códigos dos "+ ANSI_GREEN+"X utilizadores (sendo X dado pelo utilizador)"+
                ANSI_RESET+" que "+ANSI_CYAN+"avaliaram mais negócios diferentes, indicando quantos"+ANSI_RESET+", sendo o critério de ordenação a ordem decrescente do número de negócios;");
        System.out.println(ANSI_YELLOW+" 9."+ ANSI_RESET +" Dado o "+ ANSI_GREEN+"código de um negócio"+ANSI_RESET+
                ", determinar o conjunto dos "+ANSI_CYAN+"X users que mais o avaliaram "+ANSI_RESET+"e, para cada um, "+ANSI_CYAN+"qual o valor médio de classificação"+ANSI_RESET+" (ordenação cf. 5);");
        System.out.println(ANSI_YELLOW+"10."+ ANSI_RESET +" Determinar para cada "+ ANSI_GREEN+"estado"+ANSI_RESET+
                ", "+ ANSI_GREEN+"cidade a cidade"+ANSI_RESET+", a "+ANSI_CYAN+"média de classificação de cada negócio"+ANSI_RESET+".");

    }

    /**
     * View das stats
     * @param businessFile Nome do ficheiro de business
     * @param usersFile Nome do ficheiro de users
     * @param reviewsFile Nome do ficheiro de reviews
     * @param businesses Nº de business
     * @param users Nº de users
     * @param reviews Nº de reviews
     * @param reviewsMonth Reviews num mês
     * @param invalidReviews Nºde reviews inválidas
     * @param notImpactReviews Nº de reviews sem impacto
     * @param businessesReviewed Nº de negocios avaliados
     * @param businessesNotReviewed Nº de negocios sem avaliação
     * @param usersReviewers Nº de users avaliadores
     * @param usersNotReviewers º de users não avaliadores
     * @param usersReviewersMonth Reviews dos users num mês
     */
    public void stats(String businessFile, String usersFile, String reviewsFile,
                      int businesses, int users, int reviews, int[] reviewsMonth,
                      int invalidReviews, int notImpactReviews, int businessesReviewed,
                      int businessesNotReviewed, int usersReviewers, int usersNotReviewers,
                      int [] usersReviewersMonth){
        StringBuilder sb = new StringBuilder();
        sb.append(" *** Estatisticas ***\n");
        sb.append("*Ficheiro de negocios lido* ").append(businessFile).append("\n");
        sb.append("*Ficheiro de utilizadores lido* ").append(usersFile).append("\n");
        sb.append("*Ficheiro de reviews lido* ").append(reviewsFile).append("\n");
        sb.append("*Negocios totais* ").append(businesses).append(" || *Negocios c/ reviews* ").append(businessesReviewed);
        sb.append(" || *Negocios s/ reviews* ").append(businessesNotReviewed).append("\n");
        sb.append("*Utilizadores totais* ").append(users).append(" || *Utilizadores c/ reviews* ").append(usersReviewers);
        sb.append(" || *Utilizadores s/ reviews* ").append(usersNotReviewers).append("\n");
        sb.append(monthTable(usersReviewersMonth,"utilizadores c/ reviews"));
        sb.append("*Reviews totais* ").append(reviews).append(" || *Reviews invalidas* ").append(invalidReviews);
        sb.append(" || *Reviews s/ impacto* ").append(notImpactReviews).append("\n");
        sb.append(monthTable(reviewsMonth,"reviews"));
        System.out.print(sb.toString());
    }

    /**
     * Tabela com meses
     * @param x Resultado dos meses
     * @param y  Nome da categoria
     * @return String mês
     */
    private String monthTable (int [] x, String y){
        StringBuilder sb = new StringBuilder();
        List<String> months = new ArrayList<>(13);
        List<String> ints = new ArrayList<>(13);
        int [] tC = new int[13];
        int total = 1;

        months.add("meses");
        ints.add(y);
        tC[0] = Math.max(5, y.length()) + 2;
        total+=tC[0] + 1;


        for(int i = 0; i < 12; i++){
            String month = StringOfMonth(i);
            String inte = Integer.toString(x[i]);
            ints.add(inte);
            months.add(month);
            tC[i+1] = Math.max(inte.length(), month.length()) + 2;
            total+=tC[i+1] + 1;
        }
        sb.append(lineDash(total)).append("|");
        for(int i = 0; i < 13; i++){
            String s = months.get(i);
            int tamS = s.length();
            int spaces = (tC[i] - tamS)/2;
            sb.append(" ".repeat(spaces)).append(s);
            if((tC[i] - tamS) % 2 != 0)
                spaces++;
            sb.append(" ".repeat(spaces)).append("|");
        }
        sb.append("\n").append(lineDash(total)).append("|");
        for(int i = 0; i < 13; i++){
            String s = ints.get(i);
            int tamS = s.length();
            int spaces = (tC[i] - tamS)/2;
            sb.append(" ".repeat(spaces)).append(s);
            if((tC[i] - tamS) % 2 != 0)
                spaces++;
            sb.append(" ".repeat(spaces)).append("|");
        }
        sb.append("\n").append(lineDash(total));
        return sb.toString();
    }

    /**
     * Inteiro para string mês
     * @param i Inteiro
     * @return String mês
     */
    private String StringOfMonth(int i){
        return new DateFormatSymbols().getMonths()[i];
    }

}
