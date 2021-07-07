package testing;

import model.*;
import org.junit.Before;
import org.junit.Test;

import java.io.IOException;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class TestController {
    private GestReviewsMVC gr;

    @Before
    public void setUp () throws IOException {
        gr = new GestReviewsMVC("src/input_files/business_full.csv","src/input_files/users_full.csv","src/input_files/reviews_1M.csv",false);
    }

    @Test
    public void testQuery1(){
        double startTime, endTime, time = 0;

        for(int i = 0; i < 10; i++) {
            startTime = System.nanoTime();
            TreeSetBusinesses x = gr.businessesNotReviewed();
            endTime = System.nanoTime();
            time += (endTime - startTime) * (Math.pow(10, -6));
        }
        time /= 10;
        System.out.println("Tempo de execução da query 1: "+String.format("%.2f",time) + " ms");
    }

    @Test
    public void testQuery2(){
        double startTime, endTime, time = 0;

        for(int i = 0; i < 10; i++) {
            startTime = System.nanoTime();
            PairInt x = gr.allReviewsAndUsers(12, 2015);
            endTime = System.nanoTime();
            time += (endTime - startTime) * (Math.pow(10, -6));
        }
        time /= 10;
        System.out.println("Tempo de execução da query 2: "+String.format("%.2f",time) + " ms");
    }

    @Test
    public void testQuery3(){
        double startTime, endTime, time = 0;
        for(int i = 0; i < 10; i++) {
            startTime = System.nanoTime();
            UserReviewerPerMonth x = gr.getUserReviewer("rKmD1FKz-XXD7spAgMCKDg");
            endTime = System.nanoTime();
            time += (endTime - startTime) * (Math.pow(10, -6));
        }
        time/=10;
        System.out.println("Tempo de execução da query 3: "+String.format("%.2f",time) + " ms");
    }
    @Test
    public void testQuery4(){
        double startTime, endTime, time = 0;
        for(int i = 0; i < 10; i++) {
            startTime = System.nanoTime();
            BusinessReviewed x = gr.allReviewsOfBusiness("8zehGz9jnxPqXtOc7KaJxA");
            endTime = System.nanoTime();
            time += (endTime - startTime) * (Math.pow(10, -6));
        }
        time/=10;
        System.out.println("Tempo de execução da query 4: "+String.format("%.2f",time) + " ms");
    }
    @Test
    public void testQuery5(){
        double startTime, endTime, time = 0;
        for(int i = 0; i < 10; i++) {
            startTime = System.nanoTime();
            Set<BusinessReviewsCount> x = gr.businessesReviewedByUser("uUPTteweJvIe1qnwTxaGXg");
            endTime = System.nanoTime();
            time += (endTime - startTime) * (Math.pow(10, -6));
        }
        time/=10;
        System.out.println("Tempo de execução da query 5: "+String.format("%.2f",time) + " ms");
    }
    @Test
    public void testQuery6(){
        double startTime, endTime, time = 0;
        for(int i = 0; i < 10; i++) {
            startTime = System.nanoTime();
            Map<Integer, List<BusinessReviewed>> x = gr.topBusinessesMostReviewedByYear(10);
            endTime = System.nanoTime();
            time += (endTime - startTime) * (Math.pow(10, -6));
        }
        time/=10;
        System.out.println("Tempo de execução da query 6: "+String.format("%.2f",time) + " ms");
    }
    @Test
    public void testQuery7(){
        double startTime, endTime, time = 0;
        for(int i = 0; i < 10; i++) {
            startTime = System.nanoTime();
            Map<String, List<BusinessReviewed>> x = gr.topBusinessesMostReviewedByCity();
            endTime = System.nanoTime();
            time += (endTime - startTime) * (Math.pow(10, -6));
        }
        time/=10;
        System.out.println("Tempo de execução da query 7: "+String.format("%.2f",time) + " ms");
    }
    @Test
    public void testQuery8(){
        double startTime, endTime, time = 0;
        for(int i = 0; i < 10; i++) {
            startTime = System.nanoTime();
            List<UserReviewer> x = gr.topUsersReviewers(10);
            endTime = System.nanoTime();
            time += (endTime - startTime) * (Math.pow(10, -6));
        }
        time/=10;
        System.out.println("Tempo de execução da query 8: "+String.format("%.2f",time) + " ms");
    }
    @Test
    public void testQuery9(){
        double startTime, endTime, time = 0;
        for(int i = 0; i < 10; i++) {
            startTime = System.nanoTime();
            List<UserReviewer> x = gr.topUsersReviewersByBusiness("wZgUAuDuEGPEzKK-PsngKQ", 10);
            endTime = System.nanoTime();
            time += (endTime - startTime) * (Math.pow(10, -6));
        }
        time/=10;
        System.out.println("Tempo de execução da query 9: "+String.format("%.2f",time) + " ms");
    }
    @Test
    public void testQuery10(){
        double startTime, endTime, time = 0;
        for(int i = 0; i < 10; i++) {
            startTime = System.nanoTime();
            BusinessesPerState x = gr.allBusinessesPerState();
            endTime = System.nanoTime();
            time += (endTime - startTime) * (Math.pow(10, -6));
        }
        time/=10;
        System.out.println("Tempo de execução da query 10: "+String.format("%.2f",time) + " ms");
    }

}
