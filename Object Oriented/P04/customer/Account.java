package customer;
import product.Media;
/**
 * An abstract class that sets up account number, the next account number, and the string function.
 * @author Roman Rattanakone
 * @version 0.2
 * @since 0.0
 */
public abstract class Account {
    private int accountNumber;
    private static int nextAccountNumber = 1;

/**
 * Constructs current account number and next account number
 * @since 0.0
 */
    public Account() {
        this.accountNumber = nextAccountNumber;
        nextAccountNumber++;
    }
/**
 * Returns the account number
 * @return the account number
 * @since 0.0
 */
    public int getAccountNumber() {
        return accountNumber;
    }
/**
 * Sets up the string function to display what is playing 
 * @param media the title and URL of the media to be played
 * @since 0.2
 */
    public abstract String play(Media media);
}