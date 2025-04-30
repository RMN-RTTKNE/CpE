package customer;
import product.Media;
/**
 * Sets up A La Carte type account with point usage and purchasing. Prints media being played if point requirement is met.
 * @author Roman Rattanakone
 * @version 0.0
 * @since 0.0
 */
public class Alacarte extends Account {
   private int pointsRemaining;
/**
 * Adds points bought to number of points remaining.
 * @param points points to be added.
 * @return the sum of the points added to the points remaining.
 * @since 0.0
 */
   public int buyPoints(int points) {
    return pointsRemaining = points + pointsRemaining;
   }
/**
 * Returns points remaining.
 * @return points left
 * @since 0.0
 */
   public int getPointsRemaining() {
    return pointsRemaining;
   }
/**
 * Overrides string to print what is playing. If insufficient funds, states purchase is necessary, the cost of the media, and points remaining.
 * @param media the title, URL, and point cost of the media to be played.
 * @return What is being played in the string format : Playing Title (url.url, 0 points) 
 * or if there are not enough points : Buy more points: Requires 5 points You have: 0 points
 */
   @Override
   public String play(Media media) { 
    if(pointsRemaining >= media.getPoints()) {
        pointsRemaining = pointsRemaining - media.getPoints();
        return "Playing " + media.toString();
       }
       else {
        return "Buy more points: Requires " + media.getPoints() + " points\nYou have: " + getPointsRemaining() + " points";
       }
   }
}