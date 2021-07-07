package testing;

import model.*;
import org.junit.Before;
import org.junit.Test;

import java.io.*;

public class TestLoad {
    private GestReviewsMVC gr;

    @Before
    public void setUp(){
        gr = new GestReviewsMVC();
    }

    @Test
    public void loadTestePorLinhas () throws IOException {
        gr = gr.reset();
        System.out.println("Leitura dos ficheiros .csv linha a linha:");

        double startTime = System.nanoTime();
        this.readBusinessesLL("src/input_files/business_full.csv");
        double endTime = System.nanoTime();
        double time = (endTime - startTime)* (Math.pow(10, -6));
        System.out.println("Tempo de execução Business: "+String.format("%.2f",time) + " ms");

        startTime = System.nanoTime();
        this.readUsersLL("src/input_files/users_full.csv",false);
        endTime = System.nanoTime();
        time = (endTime - startTime)* (Math.pow(10, -6));
        System.out.println("Tempo de execução User: "+String.format("%.2f",time) + " ms");

        startTime = System.nanoTime();
        this.readReviewsLL("src/input_files/reviews_1M.csv");
        endTime = System.nanoTime();
        time = (endTime - startTime)* (Math.pow(10, -6));
        System.out.println("Tempo de execução Review: "+String.format("%.2f",time) + " ms");
    }

    @Test

    public void loadTesteCaractereACaractere () throws IOException{
        gr = gr.reset();
        System.out.println("Leitura dos ficheiros .csv caractere a caractere:");

        double startTime = System.nanoTime();
        this.readBusinessesLC("src/input_files/business_full.csv");
        double endTime = System.nanoTime();
        double time = (endTime - startTime)* (Math.pow(10, -6));
        System.out.println("Tempo de execução Business: "+String.format("%.2f",time) + " ms");

        startTime = System.nanoTime();
        this.readUsersLC("src/input_files/users_full.csv",false);
        endTime = System.nanoTime();
        time = (endTime - startTime)* (Math.pow(10, -6));
        System.out.println("Tempo de execução User: "+String.format("%.2f",time) + " ms");

        startTime = System.nanoTime();
        this.readReviewsLC("src/input_files/reviews_1M.csv");
        endTime = System.nanoTime();
        time = (endTime - startTime)* (Math.pow(10, -6));
        System.out.println("Tempo de execução Review: "+String.format("%.2f",time) + " ms");
    }

    @Test
    public void testObjectBuffer () throws IOException, ClassNotFoundException {
        gr = gr.reset();
        System.out.println("Leitura dos ficheiros objeto com buffer:");

        double startTime = System.nanoTime();
        gr = readObjectBuffer("gestReviews.dat");
        double endTime = System.nanoTime();
        double time = (endTime - startTime)* (Math.pow(10, -6));
        System.out.println("Tempo de execução: "+String.format("%.2f",time) + " ms");
    }

    @Test
    public void testObjectNoBuffer () throws IOException, ClassNotFoundException {
        gr = gr.reset();
        System.out.println("Leitura dos ficheiros objeto sem buffer:");

        double startTime = System.nanoTime();
        gr = readObjectNoBuffer("gestReviews.dat");
        double endTime = System.nanoTime();
        double time = (endTime - startTime)* (Math.pow(10, -6));
        System.out.println("Tempo de execução: "+String.format("%.2f",time) + " ms");
    }

    public void readBusinessesLL(String businessesFile) throws IOException{
        BufferedReader reader = new BufferedReader(new FileReader(businessesFile));
        String l;
        while (reader.ready()) {
            l = reader.readLine();
            Business b = new Business(l);
            if(gr.valid(b)){
                gr.add(b);
            }
        }
        reader.close();
    }

    public void readReviewsLL(String reviewsFile) throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader(reviewsFile));
        String l;
        while (reader.ready()){
            l = reader.readLine();
            Review r = new Review(l);
            if(gr.valid(r)) {
                gr.add(r);
            }
        }
        reader.close();
    }

    public void readUsersLL(String usersFile, boolean loadFriends) throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader(usersFile));
        String l;
        while (reader.ready()) {
            l = reader.readLine();
            User u = new User(l,loadFriends);
            if (gr.valid(u)) {
                gr.add(u);
            }
        }
        reader.close();
    }

    private void readBusinessesLC(String businessesFile) throws IOException {
        BufferedReader r = new BufferedReader(new FileReader(businessesFile));
        StringBuilder line = new StringBuilder();
        int c;
        while((c=r.read())!=-1){
            if((char) c == '\n'){
                Business b = new Business(line.toString());
                if (gr.valid(b))
                    gr.add(b);
                line = new StringBuilder();
            }
            else line.append((char) c);
        }
    }

    private void readUsersLC(String usersFile, boolean leFriends) throws IOException {
        BufferedReader r = new BufferedReader(new FileReader(usersFile));
        StringBuilder line = new StringBuilder();
        int c;
        while((c=r.read())!=-1){
            if((char) c == '\n'){
                User u = new User(line.toString(),leFriends);
                if (gr.valid(u))
                    gr.add(u);
                line = new StringBuilder();
            }
            else line.append((char) c);
        }
    }

    private void readReviewsLC(String reviewsFile) throws IOException {
        BufferedReader r = new BufferedReader(new FileReader(reviewsFile));
        StringBuilder line = new StringBuilder();
        int c;
        while((c=r.read())!=-1){
            if((char) c == '\n'){
                Review rv = new Review(line.toString());
                if (gr.valid(rv))
                    gr.add(rv);
                line = new StringBuilder();
            }
            else line.append((char) c);
        }
    }

    public GestReviewsMVC readObjectBuffer(String objectFile) throws IOException, ClassNotFoundException {
        File f = new File(objectFile);
        FileInputStream fis = new FileInputStream(f);
        ObjectInputStream ois = new ObjectInputStream(new BufferedInputStream(fis, 16*2024));
        GestReviewsMVC gr;
        if((gr = (GestReviewsMVC) ois.readObject())!=null){
            ois.close();
            return gr;
        }
        ois.close();
        return null;
    }

    public GestReviewsMVC readObjectNoBuffer(String objectFile) throws IOException, ClassNotFoundException {
        File f = new File(objectFile);
        FileInputStream fis = new FileInputStream(f);
        ObjectInputStream ois = new ObjectInputStream(fis);
        GestReviewsMVC gr;
        if((gr = (GestReviewsMVC) ois.readObject())!=null){
            ois.close();
            return gr;
        }
        ois.close();
        return null;
    }

}
