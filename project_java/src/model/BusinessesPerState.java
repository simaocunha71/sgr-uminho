package model;

import java.util.*;

/**
 * Classe auxiliar de query 10
 */
public class BusinessesPerState {
    Map<String, Map<String, Map<String,BusinessReviewed>>> businesses;
    //State//City//Id

    /**
     * Construtor vazio de BusinessesPerState
     */
    public BusinessesPerState(){
        businesses = new HashMap<>();
    }

    /**
     * Adiciona um estado
     * @param state Estado
     */
    public void addState(String state){
        businesses.put(state,new HashMap<>());
    }

    /**
     * Verifica se existe estado
     * @param state Estado
     * @return true se sim, false caso contrário
     */
    public boolean existState(String state){
        return businesses.containsKey(state);
    }

    /**
     * Adiciona uma cidade
     * @param state Estado
     * @param city Cidade
     */
    public void addCity(String state, String city){
        if(!existState(state))
            addState(state);
        businesses.get(state).put(city,new HashMap<>());
    }

    /**
     * Verifica se existe Cidade
     * @param state Estado
     * @param city Cidade
     * @return true se sim, false caso contrário
     */
    public boolean existCity(String state, String city){
        return existState(state) && businesses.get(state).containsKey(city);
    }

    /**
     * Verifica se existe um business
     * @param b Business
     * @return true se sim, false caso contrário
     */
    public boolean existBusiness(Business b){
        String city = b.getCity();
        String state = b.getState();
        String id = b.getId();
        return existCity(state, city) && businesses.get(state).get(city).containsKey(id);
    }

    /**
     * Adiciona um business
     * @param b Busieness
     */
    public void addBusiness (Business b){
        String city = b.getCity();
        String state = b.getState();
        String id = b.getId();

        if(!existCity(state,city))
            addCity(state,city);

        if(!existBusiness(b))
            businesses.get(state).get(city).put(id,new BusinessReviewed(b.getId()));
    }

    /**
     * Atualiza um business com uma review
     * @param b Business
     * @param r Review
     */
    public void updateBusiness (Business b, Review r){
        if(!existBusiness(b))
            addBusiness(b);
        businesses.get(b.getState()).get(b.getCity()).get(b.getId()).addReview(r);
    }

    /**
     * Devolve uma lista auxiliar em query 10
     * @return Lista auxiliar em query 10
     */
    public List<List<String>> getBusinessByStateNCity(){
        List<List<String>> lines = new ArrayList<>();
        businesses.forEach((state,mapCities) -> mapCities.forEach((city,mapBusinesses) -> mapBusinesses.forEach((id,b) -> {
            List<String> line = new ArrayList<>(4);
            line.add(state);
            line.add(city);
            line.add(id);
            line.add(String.format("%.2f" ,b.getAverageScore()));
            lines.add(line);
        })));
        return lines;
    }

}
