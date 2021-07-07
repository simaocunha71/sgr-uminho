package controller;

import model.*;
import view.Errors;
import view.Menu;
import view.Messages;
import view.ViewQueries;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.text.DateFormatSymbols;
import java.time.LocalDate;
import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * Classe de controlo do programa
 */
public class ControlGestReviews{

    private GestReviewsMVC gr;
    private final Scanner scan = new Scanner(System.in);
    private final Errors errors = new Errors();
    private final Messages messages = new Messages();

    private final String[] menuPrincipal = new String[]{
            "Menu Principal",
            "Carregar Dados",
            "Analisar Dados",
            "Gravar Dados"};

    private final String[] menuCarregarDados = new String[]{
            "Carregar Dados",
            "Ficheiros CSV",
            "Ficheiro Objeto"};

    private final String[] menuComAmigos = new String[]{
            "Carregar Friends",
            "Sim",
            "Não"};

    private final String[] menuCarregarCSV = new String[]{
            "Carregar CSV",
            "Default",
            "Personalizado"};

    private final String[] lerObjeto = new String[]{
            "Carregar Objeto",
            "Default",
            "Personalizado"};

    private final String[] gravarObjeto = new String[]{
            "Gravar Objeto",
            "Default",
            "Personalizado"};

    private final String[] analisarDados = new String[]{
            "Analisar dados",
            "Queries",
            "Estatisticas",
            "Catalogos"
    };

    private final String[] menuCatalogs = new String[]{
            "Catalogos",
            "Catalogo de Utilizadores",
            "Catalogo de Negocios",
            "Catalogo de Reviews"
    };

    private final String[] menuQueries = new String[]{
            "Queries",
            "Query 1",
            "Query 2",
            "Query 3",
            "Query 4",
            "Query 5",
            "Query 6",
            "Query 7",
            "Query 8",
            "Query 9",
            "Query 10",
            "Manual das Queries"};

    /**
     * Construtor vazio de ControlGestReviews
     */
    public ControlGestReviews() {
        this.gr = new GestReviewsMVC();
    }

    /**
     * Executa o menu inicial
     * @throws IOException Exceção
     * @throws ClassNotFoundException Exceção
     */
    public void run() throws IOException, ClassNotFoundException{
        Menu m = new Menu(menuPrincipal);
        m.setPreCondition(new int[]{2,3},()->gr.notEmpty());
        m.setHandler(1, this::carregarDados);
        m.setHandler(2, this::analisarDados);
        m.setHandler(3, this::gravarObjeto);
        m.run();
    }

    /**
     * Menu para gravar um objeto
     * @throws IOException Exceção
     * @throws ClassNotFoundException Exceção
     */
    private void gravarObjeto() throws IOException, ClassNotFoundException {
        Menu m = new Menu(gravarObjeto);
        m.setHandler(1,()->{
            messages.savingObject("gestReviews.dat");
            gr.saveObject("gestReviews.dat");
            messages.savingFinish();
            m.stop();
        });
        m.setHandler(2,()->{
            messages.askObject();
            String objectFile = scan.nextLine();
            messages.savingObject(objectFile);
            gr.saveObject(objectFile);
            messages.savingFinish();
            m.stop();
        });
        m.run();
    }

    /**
     * Menu para carregar dados
     * @throws IOException Exceção
     * @throws ClassNotFoundException Exceção
     */
    private void carregarDados() throws IOException, ClassNotFoundException {
        Menu m = new Menu(menuCarregarDados);
        m.setHandler(1, ()->{carregarAmigos();m.stop();});
        m.setHandler(2, ()->{carregarObjeto();m.stop();});
        m.run();
    }

    /**
     * Menu para carregar objetos
     * @throws IOException Exceção
     * @throws ClassNotFoundException Exceção
     */
    private void carregarObjeto() throws IOException, ClassNotFoundException{
        Menu m = new Menu(lerObjeto);
        m.setHandler(1, ()->{
            try{
                gr = gr.reset();
                messages.loadingObject("gestReviews.dat");
                double startTime = System.nanoTime();
                gr = gr.readObject("gestReviews.dat");
                double endTime = System.nanoTime();
                double time = (endTime - startTime)* (Math.pow(10, -6));
                messages.loadingFinish(time);

                m.stop();
            }
            catch(FileNotFoundException e){
                errors.errorFile("gestReviews.dat");
            }
        });
        m.setHandler(2, ()->{
            messages.askObject();
            String objectFile = scan.nextLine();
            try{
                gr.reset();
                messages.loadingObject(objectFile);
                double startTime = System.nanoTime();
                gr = gr.readObject(objectFile);
                double endTime = System.nanoTime();
                double time = (endTime - startTime)* (Math.pow(10, -6));
                messages.loadingFinish(time);

                m.stop();
            }
            catch(FileNotFoundException e){
                errors.errorFile(objectFile);
            }
        });
        m.run();
    }

    /**
     * Menu para carregar amigos
     * @throws IOException Exceção
     * @throws ClassNotFoundException Exceção
     */
    private void carregarAmigos() throws IOException, ClassNotFoundException{
        Menu m = new Menu(menuComAmigos);
        m.setHandler(1,()->{ficheirosCSV(true);m.stop();} );
        m.setHandler(2,()->{ficheirosCSV(false);m.stop();});
        m.run();
    }

    /**
     * Menu para os ficheiros CSV
     * @param amigos Booleano para carregar friends do user
     * @throws IOException Exceção
     * @throws ClassNotFoundException Exceção
     */
    private void ficheirosCSV(boolean amigos) throws IOException, ClassNotFoundException{
        Menu m = new Menu(menuCarregarCSV);
        m.setHandler(1,()->{
            try{
                gr = gr.reset();
                messages.loadingFiles();
                double startTime = System.nanoTime();
                gr.readSGR("src/input_files/business_full.csv",
                        "src/input_files/users_full.csv",
                        "src/input_files/reviews_1M.csv",amigos);
                double endTime = System.nanoTime();
                double time = (endTime - startTime)* (Math.pow(10, -6));
                messages.loadingFinish(time);
                m.stop();
            }
            catch(FileNotFoundException e){
                errors.errorFiles("src/input_files/business_full.csv",
                        "src/input_files/users_full.csv",
                        "src/input_files/reviews_1M.csv");
            }
        });
        m.setHandler(2,()->{
            String businessesFile, usersFile, reviewsFile;
            messages.askFile("businesses");
            businessesFile = scan.nextLine();
            messages.askFile("users");
            usersFile = scan.nextLine();
            messages.askFile("reviews");
            reviewsFile = scan.nextLine();
            try{
                gr = gr.reset();
                messages.loadingFiles();
                double startTime = System.nanoTime();
                gr.readSGR(businessesFile, usersFile, reviewsFile,amigos);
                double endTime = System.nanoTime();
                double time = (endTime - startTime)* (Math.pow(10, -6));
                messages.loadingFinish(time);
                m.stop();
            }
            catch(FileNotFoundException e){
                errors.errorFiles(businessesFile,usersFile,reviewsFile);
            }
        });
        m.run();
    }

    /**
     * Menu para analisar dados
     * @throws IOException Exceção
     * @throws ClassNotFoundException Exceção
     */
    private void analisarDados() throws IOException, ClassNotFoundException{
        Menu m = new Menu(analisarDados);
        m.setHandler(1, this::queries);
        m.setHandler(2, this::stats);
        m.setHandler(3, this::catalogs);
        m.run();
    }

    /**
     * Menu para os catalogos
     * @throws IOException Exceção
     * @throws ClassNotFoundException Exceção
     */
    private void catalogs() throws IOException, ClassNotFoundException {
        Menu m = new Menu(menuCatalogs);
        m.setHandler(1, this::catalogUsers);
        m.setHandler(2, this::catalogBusinesses);
        m.setHandler(3, this::catalogReviews);
        m.run();
    }

    /**
     * Menu para as stats
     * @throws IOException Exceção
     * @throws ClassNotFoundException Exceção
     */
    private void stats() throws IOException, ClassNotFoundException{
        Menu m = new Menu(new String[]{""});
        ViewQueries vq = new ViewQueries();
        vq.stats(gr.lastBusinessesFileRead(), gr.lastUsersFileRead(), gr.lastReviewsFileRead(),
                gr.businessesAmount(),gr.usersAmount(),gr.reviewsAmount(),gr.reviewsAmountMonth(),
                gr.invalidReviewsAmount(),gr.reviewsWithoutImpactAmount(),gr.reviewedBusinessesAmount(),
                gr.notReviewedBusinessesAmount(),gr.usersReviewersAmount(),gr.notUsersReviewersAmount(),
                gr.usersReviewersAmountMonth()
        );
        m.run();
    }

    /**
     * Menu para o help de queries
     * @throws IOException Exceção
     * @throws ClassNotFoundException Exceção
     */
    private void helpQueries()throws IOException, ClassNotFoundException {
        Menu m = new Menu(new String[]{""});
        ViewQueries vq = new ViewQueries();
        vq.help();
        m.run();
    }

    /**
     * Devolve um inteiro
     * @return Inteiro
     */
    private int auxScanTop (){
        int i;
        do {
            try {
                i = Integer.parseInt(scan.nextLine());
            } catch (NumberFormatException e) {
                i = -1;
            }
            if (!(i >= 1))
                errors.errorMonth();
        } while(!(i >= 1));

        return i;
    }

    /**
     * Devolve o mês
     * @return Mês
     */
    private int auxScanMonth (){
        int i;
        do {
            try {
                i = Integer.parseInt(scan.nextLine());
            } catch (NumberFormatException e) {
                i = -1;
            }
            if (!(i >= 1 && i <= 12))
                errors.errorMonth();
        } while(!(i >= 1 && i <= 12));

        return i;
    }

    /**
     * Devolve um ano
     * @return Ano
     */
    private int auxScanYear (){
        int i;
        int maxYear = LocalDate.now().getYear();
        do {
            try {
                i = Integer.parseInt(scan.nextLine());
            } catch (NumberFormatException e) {
                i = -1;
            }
            if (!(i >= 2000 && i <= maxYear))
                errors.errorYear();
        } while(!(i >= 2000 && i <= maxYear));

        return i;
    }

    /**
     * Escolhe uma pagina
     * @param page Pagina a escolher
     * @param currentPage Pagina atual
     * @param maxPage Pagina máxima
     * @return true se foi bem sucedido, false caso contrário
     */
    private boolean pickPage(AtomicInteger page, AtomicInteger currentPage, int maxPage){
        boolean validPage = true;
        boolean exit = false;
        String line = scan.nextLine();
        try {
            page.set(Integer.parseInt(line));
            if(page.get()>maxPage || page.get()<1) {
                page.set(currentPage.get());
                validPage = false;
            }
        } catch (NumberFormatException e) {
            page.set(currentPage.get());
            switch (line) {
                case "v":
                    exit = true;
                    break;
                case "s":
                    page.incrementAndGet();
                    if(page.get()>maxPage)
                        page.set(1);
                    break;
                case "a":
                    page.decrementAndGet();
                    if(page.get()<1)
                        page.set(maxPage);
                    break;
                default:
                    validPage = false;
            }
        }
        if(!validPage)
            errors.errorPage();
        return !exit;
    }

    /**
     * Faz a paginação para queries
     * @param colunes Colunas
     * @param lines Linhas
     * @param nameQuery Nome da query
     * @param time Tempo de execução
     */
    private void queryPagination(List<String> colunes, List<List<String>> lines, String nameQuery, double time){
        ViewQueries v = new ViewQueries();
        if(time > 0.0) v.executionTime(time);
        int toIndexMax = lines.size();
        AtomicInteger page = new AtomicInteger(1);
        AtomicInteger currentPage = new AtomicInteger(1);
        int maxPages = toIndexMax/10;
        if(toIndexMax%10 != 0) maxPages++;
        do {
            currentPage.set(page.get());
            int fromIndex = page.get()*10-10;
            int toIndex = page.get()*10;
            if(toIndex > toIndexMax)
                toIndex = toIndexMax;
            List<List<String>> linesPage = lines.subList(fromIndex,toIndex);
            v.viewQuery(colunes,linesPage,page.get(),maxPages,nameQuery,toIndexMax);}
        while(pickPage(page,currentPage,maxPages));
    }

    /**
     * Menu do catalogo de users
     */
    private void catalogUsers(){
        List<User> lu = gr.getUsersCatalog();
        List<List<String>> lines = new ArrayList<>();
        lu.forEach(u -> {
            List<String> line = new ArrayList<>(2);
            line.add(u.getId());
            line.add(u.getName());
            lines.add(line);
        });
        String nameQuery = "Utilizadores totais";
        List<String> colunes = new ArrayList<>(2);
        colunes.add(0,"Identificadores");
        colunes.add(1,"Nomes");
        queryPagination(colunes,lines,nameQuery, 0.0);
    }

    /**
     * Menu do catalogo de business
     */
    private void catalogBusinesses(){
        List<Business> lb = gr.getBusinessesCatalog();
        List<List<String>> lines = new ArrayList<>();
        lb.forEach(b -> {
            List<String> line = new ArrayList<>(4);
            line.add(b.getId());
            line.add(b.getName());
            line.add(b.getState());
            line.add(b.getCity());
            lines.add(line);
        });
        String nameQuery = "Utilizadores totais";
        List<String> colunes = new ArrayList<>(4);
        colunes.add(0,"Identificadores");
        colunes.add(1,"Nomes");
        colunes.add(1,"Estado");
        colunes.add(1,"Cidade");
        queryPagination(colunes,lines,nameQuery, 0.0);
    }

    /**
     * Menu do catalogo de reviews
     */
    private void catalogReviews(){
        List<Review> lr = gr.getReviewsCatalog();
        List<List<String>> lines = new ArrayList<>();
        lr.forEach(r -> {
            List<String> line = new ArrayList<>(8);
            line.add(r.getId());
            line.add(r.getBusinessId());
            line.add(r.getUserId());
            line.add(String.format("%.2f",r.getStars()));
            line.add(Integer.toString(r.getUseful()));
            line.add(Integer.toString(r.getFunny()));
            line.add(Integer.toString(r.getCool()));
            line.add(r.getDate().toString());
            lines.add(line);
        });
        String nameQuery = "Utilizadores totais";
        List<String> colunes = new ArrayList<>(8);
        colunes.add(0,"Identificadores");
        colunes.add(1,"Id do Negocio");
        colunes.add(2,"Id do Utilizador");
        colunes.add(3,"Estrelas dadas");
        colunes.add(4,"Util");
        colunes.add(5,"Engracado");
        colunes.add(6,"Fixe");
        colunes.add(7,"Data");
        queryPagination(colunes,lines,nameQuery, 0.0);
    }

    /**
     * Menu da query 1
     */
    private void query1(){
        double startTime = System.nanoTime();
        TreeSetBusinesses tsb = gr.businessesNotReviewed();
        double endTime = System.nanoTime();
        double time = (endTime - startTime)* (Math.pow(10, -6));
        List<String> ids = tsb.getBusinessesNotReviewedId();
        List<String> names = tsb.getBusinessesNotReviewedName();
        List<List<String>> lines = new ArrayList<>();
        int toIndexMax = tsb.getTotal();
        for(int i = 0; i < toIndexMax; i++){
            List<String> line = new ArrayList<>(2);
            line.add(ids.get(i));
            line.add(names.get(i));
            lines.add(line);
        }
        String nameQuery = "Negocios s/ reviews";
        List<String> colunes = new ArrayList<>(2);
        colunes.add(0,"Identificador");
        colunes.add(1,"Nome do Negocio");
        queryPagination(colunes,lines,nameQuery, time);
    }

    /**
     * Menu da query 2
     * @param month Mês
     * @param year Ano
     */
    private void query2(int month, int year){
        double startTime = System.nanoTime();
        PairInt p = gr.allReviewsAndUsers(month,year);
        double endTime = System.nanoTime();
        double time = (endTime - startTime)* (Math.pow(10, -6));
        List<List<String>> lines = new ArrayList<>(1);
        List<String> line = new ArrayList<>(2);
        line.add(Integer.toString(p.getOne()));
        line.add(Integer.toString(p.getTwo()));
        lines.add(line);
        String nameQuery = "";
        List<String> colunes = new ArrayList<>(2);
        colunes.add(0,"N. de Reviews");
        colunes.add(1,"N. de Users (Distintos)");
        queryPagination(colunes,lines,nameQuery, time);
    }

    /**
     * Menu da query 3
     * @param id id
     */
    private void query3(String id){
        double startTime = System.nanoTime();
        UserReviewerPerMonth ur = gr.getUserReviewer(id);
        double endTime = System.nanoTime();
        double time = (endTime - startTime)* (Math.pow(10, -6));
        List<List<String>> lines = new ArrayList<>();
        for(int i = 0; i < 12; i++){
            List<String> line = new ArrayList<>(4);
            line.add(StringOfMonth(i));
            line.add(Integer.toString(ur.getReviewsAmount(i+1)));
            line.add(Integer.toString(ur.businessReviewedAmount(i+1)));
            line.add(String.format("%.2f" ,ur.getAverageScore(i+1)));
            lines.add(line);
        }
        String nameQuery = "";
        List<String> colunes = new ArrayList<>(4);
        colunes.add(0,"Meses");
        colunes.add(1,"N. de Reviews");
        colunes.add(2,"N. de Negocios (Distintos) Avaliados");
        colunes.add(3,"Media");
        queryPagination(colunes,lines,nameQuery, time);
    }

    /**
     * Menu da query 4
     * @param id Id
     */
    private void query4(String id){
        double startTime = System.nanoTime();
        BusinessReviewed br = gr.allReviewsOfBusiness(id);
        double endTime = System.nanoTime();
        double time = (endTime - startTime)* (Math.pow(10, -6));
        List<List<String>> lines = new ArrayList<>();
        for(int i = 0; i < 12; i++){
            List<String> line = new ArrayList<>(4);
            line.add(StringOfMonth(i));
            line.add(Integer.toString(br.getReviewsAmount(i+1)));
            line.add(Integer.toString(br.getUsersReviewersAmount(i+1)));
            line.add(String.format("%.2f" ,br.getAverageScore(i+1)));
            lines.add(line);
        }
        String nameQuery = "";
        List<String> colunes = new ArrayList<>(4);
        colunes.add(0,"Meses");
        colunes.add(1,"N. de Reviews");
        colunes.add(2,"N. de Users (Distintos)");
        colunes.add(3,"Media");
        queryPagination(colunes,lines,nameQuery, time);
    }

    /**
     * Menu da query 5
     * @param id Id
     */
    private void query5(String id){
        double startTime = System.nanoTime();
        Set<BusinessReviewsCount> br = gr.businessesReviewedByUser(id);
        double endTime = System.nanoTime();
        double time = (endTime - startTime)* (Math.pow(10, -6));
        List<List<String>> lines = new ArrayList<>();
        for (BusinessReviewsCount b : br) {
            List<String> line = new ArrayList<>(2);
            line.add(b.getBusinessName());
            line.add(Integer.toString(b.getTotalReviews()));
            lines.add(line);
        }
        String nameQuery = "";
        List<String> colunes = new ArrayList<>(2);
        colunes.add(0,"Nome do Negocio");
        colunes.add(1,"N. de Reviews");
        queryPagination(colunes,lines,nameQuery, time);
    }

    /**
     * Menu da query 6
     * @param top Top
     */
    private void query6(int top){
        double startTime = System.nanoTime();
        Map<Integer, List<BusinessReviewed>> m = gr.topBusinessesMostReviewedByYear(top);
        double endTime = System.nanoTime();
        double time = (endTime - startTime)* (Math.pow(10, -6));
        List<List<String>> lines = new ArrayList<>();
        m.forEach((year, l)->{
            AtomicInteger i = new AtomicInteger(0);
            l.forEach(br->{
                i.getAndIncrement();
                List<String> line = new ArrayList<>(4);
                line.add (Integer.toString(i.get()));
                line.add (Integer.toString(year));
                line.add (br.getId());
                line.add (Integer.toString(br.getUsersReviewersAmount()));
                lines.add(line);
            });
        });
        String nameQuery = "";
        List<String> colunes = new ArrayList<>(4);
        colunes.add(0,"#");
        colunes.add(1,"Ano");
        colunes.add(2,"Id do Negocio");
        colunes.add(3,"N. de Users (Distintos)");
        queryPagination(colunes,lines,nameQuery, time);
    }

    /**
     * Menu da query 7
     */
    private void query7(){
        double startTime = System.nanoTime();
        Map<String, List<BusinessReviewed>> m = gr.topBusinessesMostReviewedByCity();
        double endTime = System.nanoTime();
        double time = (endTime - startTime)* (Math.pow(10, -6));
        List<List<String>> lines = new ArrayList<>();
        m.forEach((city, l)->{
            AtomicInteger i = new AtomicInteger(0);
            l.forEach(br->{
                i.getAndIncrement();
                List<String> line = new ArrayList<>(4);
                line.add (Integer.toString(i.get()));
                line.add (city);
                line.add (br.getId());
                line.add (Integer.toString(br.getReviewsAmount()));
                lines.add(line);
            });
        });
        String nameQuery = "";
        List<String> colunes = new ArrayList<>(4);
        colunes.add(0,"#");
        colunes.add(1,"Cidade");
        colunes.add(2,"Id do Negocio");
        colunes.add(3,"N. de Reviews");
        queryPagination(colunes,lines,nameQuery, time);
    }

    /**
     * Menu da query 8
     * @param top Top
     */
    private void query8(int top){
        double startTime = System.nanoTime();
        List<UserReviewer> l = gr.topUsersReviewers(top);
        double endTime = System.nanoTime();
        double time = (endTime - startTime)* (Math.pow(10, -6));
        List<List<String>> lines = new ArrayList<>();
        AtomicInteger i = new AtomicInteger(0);
        l.forEach(ur->{
            i.getAndIncrement();
            List<String> line = new ArrayList<>(3);
            line.add (Integer.toString(i.get()));
            line.add (ur.getId());
            line.add (Integer.toString(ur.businessReviewedAmount()));
            lines.add(line);
        });
        String nameQuery = "";
        List<String> colunes = new ArrayList<>(3);
        colunes.add(0,"#");
        colunes.add(1,"Id do Utilizador");
        colunes.add(2,"N. de Negocios (Distinos) Avaliados");
        queryPagination(colunes,lines,nameQuery, time);
    }

    /**
     * Menu da query 9
     * @param id Id
     * @param top Top
     */
    private void query9(String id, int top){
        double startTime = System.nanoTime();
        List<UserReviewer> l = gr.topUsersReviewersByBusiness(id,top);
        double endTime = System.nanoTime();
        double time = (endTime - startTime)* (Math.pow(10, -6));
        List<List<String>> lines = new ArrayList<>();
        AtomicInteger i = new AtomicInteger(0);
        l.forEach(ur->{
            i.getAndIncrement();
            List<String> line = new ArrayList<>(4);
            line.add (Integer.toString(i.get()));
            line.add (ur.getId());
            line.add(Integer.toString(ur.getReviewsAmount()));
            line.add(String.format("%.2f" ,ur.getAverageScore()));
            lines.add(line);
        });
        String nameQuery = "";
        List<String> colunes = new ArrayList<>(4);
        colunes.add(0,"#");
        colunes.add(1,"Id do Utilizador");
        colunes.add(2, "N. de Reviews");
        colunes.add(3,"Média");
        queryPagination(colunes,lines,nameQuery, time);
    }

    /**
     * Menu da query 10
     */
    private void query10(){
        double startTime = System.nanoTime();
        BusinessesPerState b = gr.allBusinessesPerState();
        double endTime = System.nanoTime();
        double time = (endTime - startTime)* (Math.pow(10, -6));
        List<List<String>> lines = b.getBusinessByStateNCity();
        String nameQuery = "";
        List<String> colunes = new ArrayList<>(4);
        colunes.add(0,"Estado");
        colunes.add(1,"Cidade");
        colunes.add(2, "Identificador do Negocio");
        colunes.add(3,"Media");
        queryPagination(colunes,lines,nameQuery, time);
    }

    /**
     * Menu das queries
     * @throws IOException Exceção
     * @throws ClassNotFoundException Exceção
     */
    private void queries() throws IOException, ClassNotFoundException {
        Menu m = new Menu(menuQueries);
        m.setHandler(1, this::query1);
        m.setHandler(2,()->{
            messages.askMonth();
            int month = auxScanMonth();
            messages.askYear();
            int year = auxScanYear();
            query2(month,year);
        });
        m.setHandler(3,()->{
            messages.askUserId();
            String id = scan.nextLine();
            if(gr.existUser(id)) {
                query3(id);
            }
            else
                errors.errorUserId();
        });
        m.setHandler(4,()->{
            messages.askBusinessId();
            String id = scan.nextLine();
            if(gr.existBusiness(id)) {
                query4(id);
            }
            else
                errors.errorBusinessId();
        });
        m.setHandler(5,()->{
            messages.askUserId();
            String id = scan.nextLine();
            if(gr.existUser(id)) {
                query5(id);
            }
            else
                errors.errorUserId();
        });
        m.setHandler(6,()->{
            messages.askTop();
            int top = auxScanTop();
            query6(top);
        });

        m.setHandler(7, this::query7);
        m.setHandler(8,()->{
            messages.askTop();
            int top = auxScanTop();
            query8(top);
        });
        m.setHandler(9,()->{
            messages.askBusinessId();
            String id = scan.nextLine();
            if(gr.existBusiness(id)) {
                messages.askTop();
                int top = auxScanTop();
                query9(id,top);
            }
            else
                errors.errorBusinessId();
        });
        m.setHandler(10, this::query10);
        m.setHandler(11, this::helpQueries);
        m.run();
    }

    /**
     * Transforma um inteiro em string mês
     * @param i Inteiro
     * @return String mês
     */
    private String StringOfMonth(int i){
        return new DateFormatSymbols().getMonths()[i];
    }
}
