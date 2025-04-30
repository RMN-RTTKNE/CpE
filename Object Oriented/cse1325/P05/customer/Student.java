package customer;
import customer.Account;
import product.Media;
/**
 * Sets up student information and account.
 * @author Roman Rattanakone
 * @version 0.2
 * @since 0.0
 */
public class Student {
    private String name;
    private int id;
    private String email;
    private Account account;
/**
 * Constructs the student's name, ID #, email, and if the studnet account is unlimited.
 * @param name the student's name.
 * @param id the student's ID #.
 * @param email the student's email ending with @uta.edu or @mavs.uta.edu.
 * @param unlimited if the student account is unlimited or not.
 * @since 0.2
 */
    public Student(String name, int id, String email, boolean unlimited) {
        if (!email.endsWith("@uta.edu") && !email.endsWith("mavs.uta.edu")) {
           throw new IllegalArgumentException ("Non-UTA email address: " + email);
        }
        this.name = name;
        this.id = id;
        this.email = email;

        if (unlimited) {
            this.account = new Unlimited();
        }
        else {
            this.account = new Alacarte();
        }
    }
/**
 * Returns the media to be played as a string.
 * @param media the name and URL of the media to be played.
 * @return the name and URL of the media to be played in the format : Playing Title (url.url, 0 points)
 * @since 0.0
 */
    public String requestMedia(Media media) {
        return account.play(media);
    }
/**
 * Returns student information as a string.
 * @return student name, ID, email, and account number in this format : John Smith (1000000000, email@uta.edu, Account #1)
 * @since 0.0
 */
    @Override
    public String toString() {
        return name + " (" + id + ", " + email + ", " + "Account #" + account.getAccountNumber() + ")\n";    
    }
/**
 * Returns the account
 * @return account, either Alacarte or Unlimited
 * @since 0.2 
 */
    public Account getAccount() {
        return account;
    }
}