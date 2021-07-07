import controller.ControlGestReviews;

import java.io.IOException;

/**
 * Classe principal do programa
 */
public class GestReviewsAppMVC {
    //Método que corre o programa
    public static void main(String[] args) throws IOException, ClassNotFoundException {
        ControlGestReviews c = new ControlGestReviews();
        c.run();
    }
}
