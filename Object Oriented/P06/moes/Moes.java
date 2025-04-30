package moes;
import java.util.ArrayList;
import product.Media;
import customer.Student;
import customer.Alacarte;
import customer.Unlimited;
import customer.Account;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
/**
 * Sets up system for buying and using points while setting up data structure of students and media.
 * @author Roman Rattanakone
 * @version 0.0
 * @since 0.0
 */
public class Moes {
    private ArrayList<Media> library; 
    private ArrayList<Student> customers;

/**
 * Adds current media to the array list of medias.
 * @param media the title, URL, and point cost of the desired media.
 * @since 0.0
*/
    public void addMedia(Media media) {
        library.add(media);
    }
/**
 * Concatenates the media array list into a readable list format.
 * @return the list of medias in the library.
 * @since 0.0
 */
    public String getMediaList() {
        StringBuilder menu = new StringBuilder();

        for (int i = 0; i < library.size(); i++) {
        Media media = library.get(i);
        menu.append(i).append(") ").append(media.toString());
    }
        return menu.toString();

    }
/**
 * Adds students to the customer array list.
 * @param student the information of the student to be added.
 * @since 0.0
 */
    public void addStudent(Student student) {
        customers.add(student);
    }
/**
 * Concatenates the customer array list into a readable list format.
 * @return the list of students in the customer array list.
 * @since 0.0
 */
    public String getStudentList() {
        StringBuilder menu = new StringBuilder();

        for (int i = 0; i < customers.size(); i++) {
        Student student = customers.get(i);
        menu.append(i).append(") ").append(student.toString());
    }
        return menu.toString();
    }
/**
 * Returns the number of points a student has. If the account is unlimited, INT_MAX is returned. Returns error if type of account does not exist.
 * @param studentIndex the index of the requested student.
 * @return points remaining (Alacarte account), unlimited points, or returns an error.
 * @since 0.0
 */
    public int getPoints(int studentIndex) {
        Account current = customers.get(studentIndex).getAccount();
        if(current instanceof Alacarte) {
            Alacarte alacarteAcc = (Alacarte)current;
            return (alacarteAcc.getPointsRemaining());
        }
        else if (current instanceof Unlimited) {
            return Integer.MAX_VALUE;
        }
        else {
            throw new UnsupportedOperationException("Unknown subclass of Account");
        }
    }
/**
 * Allows points to be added to a student's account. If unlimited, the option is skipped. Returns error if type of account does not exist.
 * @param studentIndex the index of the student's account. 
 * @param points the amount of points to be added. 
 * @return the new sum of the student's points if bought. If account was unlimited, option is skipped. Returns error if type of account does not exist. 
 * @since 0.0
 */
    public String buyPoints(int studentIndex, int points) {
        Account current = customers.get(studentIndex).getAccount();
        if(current instanceof Alacarte) {
            Alacarte alacarteAcc = (Alacarte)current;
            int sum = alacarteAcc.buyPoints(points);
            return "Student has " + sum + " points.";
        }
        else if(current instanceof Unlimited) {
            return "Student has unlimited account. No additional points required.";
        }
        else {
            throw new UnsupportedOperationException("Unknown subclass of Account");
        }
    }
/**
 * Returns the media playing and the number of points remaining on the account.
 * @param studentIndex the index of the student's account.
 * @param mediaIndex the index of the media to be played.
 * @return the title, url, and number of points remaining in this format : Playing Title (url.url, 0 points)
 * @since 0.0
 */
    public String playMedia(int studentIndex, int mediaIndex) {
        return customers.get(studentIndex).requestMedia(library.get(mediaIndex));
    }

    public Moes() {
        library = new ArrayList<>();
        customers = new ArrayList<>();
    }

    public Moes(BufferedReader br) throws IOException {
        int size = Integer.parseInt(br.readLine());
        library = new ArrayList<>();
        for(int i = 0; i < size; i++) library.add(new Media(br));

        int size2 = Integer.parseInt(br.readLine());
        customers = new ArrayList<>();
        for(int i = 0; i < size2; i++) customers.add(new Student(br));
    }

    public void save(BufferedWriter bw) throws IOException {
        bw.write("" + library.size() + '\n');
        for(Media mloop : library) mloop.save(bw);

        bw.write("" + customers.size() + '\n'); 
        for(Student sloop : customers) sloop.save(bw);
    }
}
