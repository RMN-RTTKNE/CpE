package test;
import product.Media;

public class TestMedia {
    public static void main(String[] args) {
        Media media = new Media("Superman: The Mechanical Monsters", "https://publicdomainmovie.net/movie/superman-the-mechanical-monsters", 0);
        
        if(!media.toString().equals("Superman: The Mechanical Monsters (https://publicdomainmovie.net/movie/superman-the-mechanical-monsters, 0 points)\n")) {
            System.err.println("FAIL: " + "Superman: The Mechanical Monsters (https://publicdomainmovie.net/movie/superman-the-mechanical-monsters, 0 points) but " + media.toString());
            System.exit(1);
        }
    }
}