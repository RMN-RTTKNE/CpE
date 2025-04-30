package product;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;

/**
 * Creates a media object to be played with a title, url, and number of points.
 * 
 * @author Roman Rattanakone
 * @version 0.2
 * @since 0.0
 */
public class Media {
    
    private String title;
    private String url;
    private int points;    

/**
 * Constructs the title, url, and points fields.
 * @param title the title of the media to be played
 * @param url the URL of the media to be played
 * @param points the amount of points the user has
 * @since 0.2
 */
    public Media(String title, String url, int points) {
        this.title = title;
        this.url = url;
        this.points = points;
    }
    public Media(BufferedReader br) throws IOException {
        this.title = br.readLine();
        this.url = br.readLine();
        this.points = Integer.parseInt(br.readLine());
    }
       
/**
 * Retrieves the amount of points the media costs to play
 * @return number of points.
 * @since 0.2
 */
    public int getPoints() {
        return points;
    }
/**
 * Prints the class as a string, displaying the media's title, its url, and the number of points.
 * @return the title, url, and number of points in this format : Title (url.url, 0 points)
 * @since 0.2
 */
    @Override 
    public String toString() {
        return title + " (" + url + ", " + getPoints() + " points)\n";
    }

    public void save(BufferedWriter bw) throws IOException {
        bw.write(title + '\n');
        bw.write(url + '\n');
        bw.write("" + points + '\n');
    }
}