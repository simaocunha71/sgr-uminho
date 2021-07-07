package model;

import model.interfacesSGR.SGR;

import java.io.*;
import java.time.LocalDate;
import java.util.*;

/**
 * Classe de modelo principal do programa
 */
public class GestReviewsMVC implements SGR {
    private Map<String, Business> businesses;
    private Map<String, User> users;
    private List<List<Review>> reviews;
    private Statistics stats;

    private final int buffer = 16*1024; //16384

    /**
     * Construtor vazio de GestReviewsMVC
     */
    public GestReviewsMVC(){
        this.businesses = new HashMap<>();
        this.reviews = new ArrayList<>();
        for(int i = 0; i < 12; i++){
            List<Review> reviewsForMonth = new ArrayList<>();
            this.reviews.add(i,reviewsForMonth);
        }
        this.users = new HashMap<>();
        this.stats = new Statistics();
    }

    /**
     * Construtor parametrizado de GestReviewsMVC
     * @param businessesFile Nome do ficheiro de business
     * @param usersFile Nome do ficheiro de users
     * @param reviewsFile Nome do ficheiro de reviews
     * @param loadFriends Booleano para o carregamento dos friends de um user
     * @throws IOException Exceção
     */
    public GestReviewsMVC(String businessesFile, String usersFile, String reviewsFile, boolean loadFriends) throws IOException {
        this();
        this.readBusinesses(businessesFile);
        this.readUsers(usersFile, loadFriends);
        this.readReviews(reviewsFile);
    }

    /**
     * Verifica se os users, reviews e businesses não estão vazios
     * @return true se não está vazia, false caso contrário
     */
    public boolean notEmpty (){
        return !businesses.isEmpty() && !users.isEmpty() && notEmptyReviews();
    }

    /**
     * Testa se uma review está vazia
     * @return true se não está vazia, false caso contrário
     */
    public boolean notEmptyReviews(){
        boolean empty = true;
        for(int i = 0; i < 12 && empty; i++){
            empty = reviews.get(i).isEmpty();
        }
        return !empty;
    }

    /**
     * Testa se existe business
     * @param businessId Id do business
     * @return true se sim, false caso contrário
     */
    public boolean existBusiness(String businessId){
        return businesses.containsKey(businessId);
    }

    /**
     * Testa se existe user
     * @param userId Id do user
     * @return true se sim, false caso contrário
     */
    public boolean existUser(String userId){
        return users.containsKey(userId);
    }

    /**
     * Adiciona um business
     * @param b Business
     */
    public void add (Business b){
        this.businesses.put(b.getId(), b.clone());
    }

    /**
     * Adiciona uma review
     * @param r Review a adicionar
     */
    public void add (Review r){
        int month = r.getDate().getMonthValue();
        this.reviews.get(month-1).add(r.clone());
        stats.addReview(r);
    }

    /**
     * Adiciona um user
     * @param u User a adicionar
     */
    public void add(User u){
        this.users.put(u.getId(), u.clone());
    }

    /**
     * Valida um user
     * @param u User a validar
     * @return true se sim, false caso contrário
     */
    public boolean valid(User u){

        return u != null && !u.getId().equals("") && !u.getName().equals("") && !users.containsKey(u.getId());
    }

    /**
     * Valida um business
     * @param b Business a validar
     * @return true se sim, false caso contrário
     */
    public boolean valid(Business b){
        return b!=null && !b.getId().equals("") && !b.getName().equals("") && !b.getCity().equals("") && !b.getState().equals("");
    }

    /**
     * Valida uma review
     * @param r Review a validar
     * @return true se sim, false caso contrário
     */
    public boolean valid(Review r){
        return r!=null && !r.getId().equals("") && !r.getBusinessId().equals("") && !r.getUserId().equals("")
                && r.getStars() >= 0 && r.getUseful() >= 0 && r.getFunny() >= 0 && r.getCool() >= 0 && r.getDate() != null
                && users.containsKey(r.getUserId()) && businesses.containsKey(r.getBusinessId());
    }

    /**
     * Devolve o catálogo dos users
     * @return Lista de users
     */
    public List<User> getUsersCatalog(){
        List<User> users = new ArrayList<>();
        for(User u : this.users.values()){
            users.add(u.clone());
        }
        return users;
    }

    /**
     * Devolve o catálogo das reviews
     * @return Lista das reviews
     */
    public List<Review> getReviewsCatalog(){
        List<Review> reviews = new ArrayList<>();
        for(int i = 0; i < 12; i++) {
            for (Review r : this.reviews.get(i)) {
                reviews.add(r.clone());
            }
        }
        return reviews;
    }

    /**
     * Devolve o catálogo dos businesses
     * @return Lista dos business
     */
    public List<Business> getBusinessesCatalog(){
        List<Business> businesses = new ArrayList<>();
        for(Business b : this.businesses.values()){
            businesses.add(b.clone());
        }
        return businesses;
    }

    /**
     * Devolve um User
     * @param id Id do user
     * @return User
     */
    public User getUser(String id) {
        return (users.containsKey(id)) ? users.get(id).clone() : null;
    }

    /**
     * Devolve um business
     * @param id Id do business
     * @return Business
     */
    public Business getBusiness(String id) {
        return (businesses.containsKey(id)) ? businesses.get(id).clone() : null;
    }

    /**
     * Devolve uma review
     * @param id Id da review
     * @return Review
     */
    public Review getReview(String id) {
        Review r = null;
        boolean found = false;
        for(int i = 0; i < 12 && !found; i++){
            List<Review> rs = this.reviews.get(i);
            for(Review review : rs) {
                if (review.getId().equals(id)){
                    r = review;
                    found = true;
                }
            }
        }
        return r;
    }

    /**
     * Incorpora a leitura dos 3 ficheiros
     * @param businessesFile Nome do ficheiro dos businesses
     * @param usersFile Nome do ficheiro dos users
     * @param reviewsFile Nome do ficheiro das reviews
     * @param loadFriends Booleano que indica se é carregada ou não os amigos de um user
     * @throws IOException Exceção
     */
    public void readSGR(String businessesFile, String usersFile, String reviewsFile, boolean loadFriends) throws IOException {
        readUsers(usersFile, loadFriends);
        readBusinesses(businessesFile);
        readReviews(reviewsFile);
    }

    /**
     * Lê o ficheiro dos business
     * @param businessesFile Nome do ficheiro
     * @throws IOException Exceção
     */
    public void readBusinesses(String businessesFile) throws IOException{
        BufferedReader reader = new BufferedReader(new FileReader(businessesFile));
        stats.setBusinessesFile(businessesFile);

        while (reader.ready()) {
            String l = reader.readLine();
            Business b = new Business(l);
            if(valid(b)){
                this.add(b);
                stats.incBusinesses();
            }
        }
        reader.close();
    }

    /**
     * Lê o ficheiro das reviews
     * @param reviewsFile Nome do ficheiro de reviews
     * @throws IOException Exceção
     */
    public void readReviews(String reviewsFile) throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader(reviewsFile));
        stats.setReviewsFile(reviewsFile);
        String l = reader.readLine();
        while (reader.ready()){
            l = reader.readLine();
            Review r = new Review(l);
            if(valid(r)) {
                add(r);
            }
            else {
                stats.incInvalidReviews();
            }

        }
        reader.close();
    }

    /**
     * Lê o ficheiro dos Users
     * @param usersFile Nome do ficheiro de users
     * @param loadFriends Booleano que indica se é carregada ou não os amigos de um user
     * @throws IOException Exceção
     */
    public void readUsers(String usersFile, boolean loadFriends) throws IOException {
        //BufferedReader reader = new BufferedReader(new FileReader("input_files/users_full.csv"));
        BufferedReader reader = new BufferedReader(new FileReader(usersFile));
        stats.setUsersFile(usersFile);

        while (reader.ready()) {
            String l = reader.readLine();
            User u = new User(l,loadFriends);
            if (valid(u)) {
                this.add(u);
                stats.incUsers();
            }
        }
        reader.close();
    }

    /**
     * Devolve o número de users
     * @return Número de users
     */
    public int usersAmount() {
        return this.stats.getUsersAmount();
    }

    /**
     * Devolve o número de Businesses
     * @return Número de Businesses
     */
    public int businessesAmount() {
        return this.stats.getBusinessesAmount();
    }

    /**
     * Devolve o número de negocios avaliados
     * @return Número de negocios avaliados
     */
    public int reviewedBusinessesAmount() {
        return this.stats.getReviewedBusinessesAmount();
    }

    /**
     * Devolve o número de negocios não avaliados
     * @return Número de negocios não avaliados
     */
    public int notReviewedBusinessesAmount() {
        return this.businessesAmount()-reviewedBusinessesAmount();
    }

    /**
     * Devolve o numero de reviews
     * @return Número de reviews
     */
    public int reviewsAmount() {
        int total = 0;
        for (int i = 0; i < 12; i++ )
            total+=reviews.get(i).size();
        return total;
    }

    /**
     * Score atribuido num ano
     * @return Score
     */
    public int[] reviewsAmountMonth() {
        int [] reviewsA = new int [12];
        for (int i = 0; i < 12; i++ )
            reviewsA[i] = reviews.get(i).size();
        return reviewsA;
    }

    /**
     * Número de reviews num mês
     * @param month Mês a procurar
     * @return Número de reviews num mês
     */
    public int reviewsAmount(int month) {
        return this.stats.getReviewsAmount(month);
    }

    /**
     * Número de reviews inválidas
     * @return Número de reviews inválidas
     */
    public int invalidReviewsAmount() {
        return stats.getReviewsInvalidAmount();
    }

    /**
     * Número de users que fizeram reviews
     * @return Users
     */
    public int usersReviewersAmount() {
        return this.stats.getUsersReviewersAmount();
    }

    /**
     * Número de users que fizeram reviews num mês
     * @param month Mês
     * @return Users
     */
    public int usersReviewersAmount(int month) {
        return this.stats.getUsersReviewersAmount(month);
    }

    /**
     * Array de score de users num mês
     * @return Array
     */
    public int [] usersReviewersAmountMonth() {
        int [] usersRA = new int [12];
        for(int i = 0; i < 12; i++){
            usersRA[i] = stats.getUsersReviewersAmount(i+1);
        }
        return usersRA;
    }

    /**
     * Numero de Users sem reviews
     * @return users
     */
    public int notUsersReviewersAmount() {
        return this.usersAmount() - usersReviewersAmount();
    }

    /**
     * Reviews sem impacto
     * @return reviews
     */
    public int reviewsWithoutImpactAmount() {
        return this.stats.getReviewsWithoutImpact();
    }

    /**
     * Reviews score num mês
     * @param month Mês a procurar
     * @return Score
     */
    public double averageReviewsScore(int month) {
        return this.stats.getReviewsAverageScore(month);
    }

    /**
     * Reviews score
     * @return Score
     */
    public double averageReviewsScore() {
        return this.stats.getReviewsAverageScore();
    }

    /**
     * Nome do ultimo ficheiro de users lido
     * @return Nome
     */
    public String lastUsersFileRead() {
        return this.stats.getUsersFile();
    }
    /**
     * Nome do ultimo ficheiro de reviews lido
     * @return Nome
     */
    public String lastReviewsFileRead() {
        return this.stats.getReviewsFile();
    }
    /**
     * Nome do ultimo ficheiro de businesses lido
     * @return Nome
     */
    public String lastBusinessesFileRead() {
        return this.stats.getBusinessesFile();
    }
    /**
     * [QUERY 1]
     * Lista ordenada alfabeticamente com os identificadores dos negócios nunca avaliados e
     * o seu respetivo total
     * @return TreeSet dos business que não foram avaliados e o total
     */
    public TreeSetBusinesses businessesNotReviewed() {
        TreeSetBusinesses r = new TreeSetBusinesses(new BusinessComp());
        Set<String> businessesReviewed = this.stats.getReviewedBusinesses();
        for(Business b: this.businesses.values()){
            if(!businessesReviewed.contains(b.getId())){
                r.add(b);
            }
        }
        return r;
    }
    /**
     * [QUERY 2]
     * Dado um mês e um ano (válidos), determinar o número total global de reviews realizadas e
     * o número total de users distintos que as realizaram
     * @param month Mês
     * @param year Ano
     * @return Tuplo com o número total global de reviews realizadas e com o número total de users
     * distintos que as realizaram
     */
    public PairInt allReviewsAndUsers(int month, int year) {
        if(!(month >= 1 && month <= 12 && year <= LocalDate.now().getYear() && year >= 1992))
            return new PairInt(-1,-1);
        PairInt result = new PairInt();
        Set<String> usersReviewers = new HashSet<>();
        for(Review r : this.reviews.get(month-1)){
            if(r.getDate().getYear() == year){
                result.incOne();
                usersReviewers.add(r.getUserId());
            }
        }
        result.incTwo(usersReviewers.size());
        return result;
    }
    /**
     * [QUERY 3]
     * Dado um código de utilizador, determinar, para cada mês, quantas reviews fez,
     * quantos negócios distintos avaliou e que nota média atribuiu
     * @param userId Id do utilizador
     * @return UserReviewerPerMonth, que inclui quantas reviews um user efetuou,
     * quantos negócios distintos avaliou e que nota média atribuiu
     */
    public UserReviewerPerMonth getUserReviewer(String userId) {
        User u = users.get(userId);
        if(u!=null) {
            UserReviewerPerMonth result = new UserReviewerPerMonth(u);
            for (int i = 0; i < 12; i++) {
                for (Review r : reviews.get(i))
                    result.addReview(r.clone());
            }
            return result;
        }
        return null;
    }
    /**
     * [QUERY 4]
     * Dado o código de um negócio, determinar, mês a mês, quantas vezes foi avaliado,
     * por quantos users diferentes e a média de classificação
     * @param businessId Id do business
     * @return BusinessReviewed, que inclui quantas vezes um negoćio foi avaliado,
     * por quantos users diferentes e a média de classificação
     */
    public BusinessReviewed allReviewsOfBusiness(String businessId) {
        BusinessReviewed result = new BusinessReviewed(businessId);
        if(this.stats.reviewedBusiness(businessId)) {
            for (int month = 1; month <= 12; month++) {
                for (Review r : this.reviews.get(month-1)){
                    if(businessId.equals(r.getBusinessId()))
                        result.addReview(r.clone());
                }
            }
        }
        return result;
    }
    /**
     * [QUERY 5]
     * Dado o código de um utilizador determinar a lista de nomes de negócios que mais
     * avaliou (e quantos), ordenada por ordem decrescente de quantidade e, para
     *  quantidades iguais, por ordem alfabética dos negócios
     * @param userId Id do user
     * @return Lista dos nomes dos negócios que esse utilizador avaliou (e quantos)
     */
    public Set<BusinessReviewsCount> businessesReviewedByUser(String userId) {
        Set <BusinessReviewsCount> result = new TreeSet<>(new BusinessReviewedComp());
        if(users.containsKey(userId)){
          UserReviewerPerMonth u = getUserReviewer(userId);
          List<String> lb = u.getAllBusinessReviewed();
          Map<String,BusinessReviewsCount> bs = new HashMap<>();
          lb.forEach(s -> {
              if(bs.containsKey(s)){
                  bs.get(s).addReview();
              }
              else {
                  Business b = this.businesses.get(s);
                  BusinessReviewsCount br = new BusinessReviewsCount(b.getId(),b.getName());
                  br.addReview();
                  bs.put(br.getBusinessId(),br);
              }
          });
          result.addAll(bs.values());
        }
        return result;
    }


    /**
     * Auxiliar para query
     * @param bs Businesses
     * @param top Top
     * @param comp Comparator
     * @return Lista de Business
     */
    public List<BusinessReviewed> auxTopBusinessesMostReviewed(Map<String,BusinessReviewed> bs, int top, Comparator<BusinessReviewed> comp){
        List<BusinessReviewed> result = new ArrayList<>();
        Set<BusinessReviewed> aux = new TreeSet<>(comp);
        aux.addAll(bs.values());
        int i = 0;
        Iterator<BusinessReviewed> iterator = aux.iterator();
        while(i < top && iterator.hasNext()){
            BusinessReviewed br = iterator.next();
            result.add(i,br);
            i++;
        }
        return result;
    }

    /**
     * Auxiliar para query
     * @param us Users
     * @param top Top
     * @param comp Comparator
     * @return Lista de Users
     */
    public List<UserReviewer> auxTopUsersReviewers(Map<String, UserReviewer> us, int top, Comparator<UserReviewer> comp){
        List<UserReviewer> result = new ArrayList<>();
        Set<UserReviewer> aux = new TreeSet<>(comp);
        aux.addAll(us.values());
        Iterator<UserReviewer> iterator = aux.iterator();
        int i = 0;
        while(i < top && iterator.hasNext()){
            UserReviewer ur = iterator.next();
            result.add(i,ur);
            i++;
        }
        return result;
    }

    /**
     * [QUERY 6]
     * Determinar o conjunto dos X negócios mais avaliados (com mais reviews) em cada
     * ano, indicando o número total de distintos utilizadores que o avaliaram
     * (X é um inteiro dado pelo utilizador)
     * @param top Primeiros top negócios
     * @return Map de business com as avaliações de cada ano
     */
    public Map<Integer, List<BusinessReviewed>> topBusinessesMostReviewedByYear(int top) {
        Map<Integer,Map<String,BusinessReviewed>> auxMap = new HashMap<>();
        Map<Integer, List<BusinessReviewed>>  result = new HashMap<>();

        for(int i = 0; i < 12; i++){
            for(Review r : reviews.get(i)){
                int year = r.getDate().getYear();
                String businessId = r.getBusinessId();
                if(auxMap.containsKey(year)){ //Ano ja com negocios
                    Map<String,BusinessReviewed> bs = auxMap.get(year); //Vai buscar a hash de negocios daquele ano
                    if(bs.containsKey(businessId)){ //se o negocio ja tiver na hash
                        BusinessReviewed br = bs.get(businessId); //busca-se o negocio
                        br.addReview(r); //adiciona-se a review
                                           }
                    else {//se o negocio ainda nao tiver na hash
                        BusinessReviewed br = new BusinessReviewed(businessId); //tem de ser criado
                        br.addReview(r); //adiciona-se a review
                        bs.put(businessId,br); //adiciona-se à hash
                    }
                }
                else{ //Ano ainda sem negocios
                    Map<String,BusinessReviewed> bs = new HashMap<>(); //cria uma hash nova
                    BusinessReviewed br = new BusinessReviewed(businessId); //como a hash é nova nao tem negocios ainda
                    br.addReview(r);
                    bs.put(businessId,br); //mete o primeiro negocio na hash
                    auxMap.put(year,bs); //mete a hash daquele ano no resultado
                }
            }
        }
        auxMap.forEach((year,value)->result.put(year,auxTopBusinessesMostReviewed(value,top,new BusinessDistinctUsersComp())));
        return result;
    }
    /**
     * [QUERY 7]
     * Determinar, para cada cidade, a lista dos três mais famosos negócios em termos de número de reviews
     * @return Map de Business com as avaliações , onde a cada chave Cidade associa-se a lista dos
     * 3 mais famosos negócios
     */
    public Map<String, List<BusinessReviewed>> topBusinessesMostReviewedByCity() {
        Map<String,Map<String,BusinessReviewed>> auxMap = new HashMap<>();
        Map<String, List<BusinessReviewed>>  result = new HashMap<>();

        for(int i = 0; i < 12; i++){
            for(Review r : reviews.get(i)){
                String businessId = r.getBusinessId();
                if(!businesses.containsKey(businessId)) {
                    break; }
                String city = this.businesses.get(businessId).getCity();
                if(auxMap.containsKey(city)){
                    Map<String,BusinessReviewed> bs = auxMap.get(city);
                    if(bs.containsKey(businessId)){
                        BusinessReviewed br = bs.get(businessId);
                        br.addReview(r);
                    }
                    else {
                        BusinessReviewed br = new BusinessReviewed(businessId);
                        br.addReview(r);
                        bs.put(businessId,br);
                    }
                }
                else{
                    Map<String,BusinessReviewed> bs = new HashMap<>();
                    BusinessReviewed br = new BusinessReviewed(businessId);
                    br.addReview(r);
                    bs.put(businessId,br);
                    auxMap.put(city,bs);
                }
            }
        }
        auxMap.forEach((city,value)->result.put(city,auxTopBusinessesMostReviewed(value,3,new BusinessTotalReviewsComp())));
        return result;
    }
    /**
     * [QUERY 8]
     * Determinar os códigos dos X utilizadores (sendo X dado pelo utilizador) que
     * avaliaram mais negócios diferentes, indicando quantos, sendo o critério de
     * ordenação a ordem decrescente do número de negócios
     * @param top Primeiros top utilizadores
     * @return Lista de utilizadores que avaliaram mais negócios diferentes
     */
    public List<UserReviewer> topUsersReviewers(int top) {
        Map<String, UserReviewer> auxMap = new HashMap<>();
        for (int i = 0; i < 12; i++) {
            for (Review r : reviews.get(i)) {
                String userId = r.getUserId();
                if (auxMap.containsKey(userId)) {
                    auxMap.get(userId).addReview(r);
                } else {
                    UserReviewer userR = new UserReviewer(users.get(userId));
                    userR.addReview(r);
                    auxMap.put(userId, userR);
                }
            }
        }
        return auxTopUsersReviewers(auxMap,top,new UserReviewerComp());
    }
    /**
     * [QUERY 9]
     * Dado o código de um negócio, determinar o conjunto dos X users que mais o
     * avaliaram e, para cada um, qual o valor médio de classificação (ordenação cf. 5)
     * @param businessId Id de um business
     * @param top Primeiros top users
     * @return Lista de users que mais fizeram reviews e o valor médio de classificação
     */
    public List<UserReviewer> topUsersReviewersByBusiness(String businessId, int top) {
        Map<String, UserReviewer> auxMap = new HashMap<>();
        for (int i = 0; i < 12; i++) {
            for (Review r : reviews.get(i)) {
                if(r.getBusinessId().equals(businessId)) {
                    String userId = r.getUserId();
                    if (auxMap.containsKey(userId)) {
                        auxMap.get(userId).addReview(r);
                    } else {
                        UserReviewer userR = new UserReviewer(users.get(userId));
                        userR.addReview(r);
                        auxMap.put(userId, userR);
                    }
                }
            }
        }
        return auxTopUsersReviewers(auxMap,top,new UserReviewerTotalReviewsComp());
    }
    /**
     * [QUERY 10]
     * Determinar para cada estado, cidade a cidade, a média de classificação de cada negócio
     * @return Map de negócios de todos os estados com a sua classificação média
     */
    public BusinessesPerState allBusinessesPerState (){
        BusinessesPerState result = new BusinessesPerState();
        businesses.values().forEach(result::addBusiness);
        reviews.forEach(l -> l.forEach(r -> result.updateBusiness(businesses.get(r.getBusinessId()),r)));
        return result;
    }

    /**
     * Grava em ficheiro objeto
     * @param objectFile Nome do ficheiro
     * @throws IOException Exceção
     */
    public void saveObject (String objectFile) throws IOException {
        File f = new File(objectFile);
        FileOutputStream fos = new FileOutputStream(f);
        ObjectOutputStream oos = new ObjectOutputStream(new BufferedOutputStream(fos, buffer));
        oos.writeObject(this);
        oos.flush();
        oos.close();
    }

    /**
     * Lê de um ficheiro objeto
     * @param objectFile Nome do ficheiro
     * @return GestReviewsMVC
     * @throws IOException Exceção
     * @throws ClassNotFoundException Exceção
     */
    public GestReviewsMVC readObject(String objectFile) throws IOException, ClassNotFoundException {
        File f = new File(objectFile);
        FileInputStream fis = new FileInputStream(f);
        ObjectInputStream ois = new ObjectInputStream(new BufferedInputStream(fis, buffer));
        GestReviewsMVC gr;
        if((gr = (GestReviewsMVC) ois.readObject())!=null){
            ois.close();
            return gr;
        }
        ois.close();
        return null;
    }

    /**
     * Limpa os businesses, reviews e users
     * @return novo GestReviewsMVC
     */
    public GestReviewsMVC reset (){
        businesses.clear();
        reviews.clear();
        users.clear();
        return new GestReviewsMVC();
    }
}
