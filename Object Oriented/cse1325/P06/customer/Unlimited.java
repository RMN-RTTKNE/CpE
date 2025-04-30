package customer;
import product.Media;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
/**
 * Sets up unlimited account and the string to display what is being played.
 * @author Roman Rattanakone
 * @version 0.0
 * @since 0.0
 */
public class Unlimited extends Account { 
/**
 * Overrides string function to display what is being played in the format : Playing Title (url.url, 0 points).
 * @param media the title and URL of the media to be played.
 * @return What is being played in the string format : Playing Title (url.url, 0 points)
 * @since 0.0
 */
    @Override
    public String play(Media media) {
        return "Playing " + media.toString();
    }

    public Unlimited() {
        super();
    }

    public Unlimited(BufferedReader br) throws IOException {
        super(br);
    }
   
    public void save(BufferedWriter bw) throws IOException {
        super.save(bw);
    }
}