public class TestMedia {
    public static void main(String[] args) {
        Media media = new Media("Superman: The Mechanical Monsters", "https://publicdomainmovie.net/movie/superman-the-mechanical-monsters");
        
        if(!media.toString().equals("Superman: The Mechanical Monsters (https://publicdomainmovie.net/movie/superman-the-mechanical-monsters)")) {
            System.err.println("FAIL: " + "Superman: The Mechanical Monsters (https://publicdomainmovie.net/movie/superman-the-mechanical-monsters) but " + media.toString());
            System.exit(1);
        }
    }
}