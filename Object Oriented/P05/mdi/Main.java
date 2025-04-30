package mdi;
import moes.Moes;
import customer.Student;
import product.Media;
import java.util.Scanner;

public class Main {
    private Moes moes;
    private String output;
    private Menu menu;
    private boolean running;

    private void addStudent() {
        Scanner in = new Scanner(System.in);
        System.out.print("Enter student name: ");
        String name = in.nextLine();
        System.out.print("Enter student ID #: ");
        int id = in.nextInt();
        in.nextLine(); //consume the buffer
        System.out.print("Enter student email: ");
        String email = in.nextLine();
        System.out.print("Enter unlimited status: ");
        boolean unlimited = in.nextBoolean(); 

        Student student = new Student(name, id, email, unlimited);
        moes.addStudent(student);
    }
    private void listStudents() {
        System.out.println(moes.getStudentList());
    }

    private void addMedia() {
        Scanner in2 = new Scanner(System.in);
        System.out.print("Enter media title: ");
        String title = in2.nextLine();
        System.out.print("Enter media URL: ");
        String url = in2.nextLine();
        System.out.print("Enter media points: ");

        int points = in2.nextInt();

        Media media = new Media(title, url, points);
        moes.addMedia(media);
    }
    private void listMedia() {
        System.out.println(moes.getMediaList());
    }
    private void playMedia() {
        Scanner in3 = new Scanner(System.in);
        System.out.print("Enter student index: ");
        int sndx = in3.nextInt();
        System.out.print("Enter media index: ");
        int mndx = in3.nextInt();

        System.out.println(moes.playMedia(sndx, mndx));
    }
    private void listAvailablePoints() {
        System.out.print("Enter student index: ");
        Scanner in4 = new Scanner(System.in);
        int sndx2 = in4.nextInt();

        System.out.println("Student has " + moes.getPoints(sndx2) + "points");
    }
    private void buyPoints() {
        System.out.print("Enter student index: ");
        Scanner in5 = new Scanner(System.in);
        Scanner in6 = new Scanner(System.in);
        int sndx3 = in5.nextInt();
        System.out.println("Available points: " + moes.getPoints(sndx3));
        System.out.print("How many points to buy? ");
        int bpoint = in6.nextInt();
        if(bpoint < 0) {
            System.out.println("Can't purchase negative points!");
        }
        

        System.out.println(moes.buyPoints(sndx3, bpoint));
    }

    public Main () {
        this.moes = new Moes();
        this.output = "";
        this.menu = new Menu();
        this.running = true;
        menu.addMenuItem(new MenuItem("Add student", () -> addStudent()));
        menu.addMenuItem(new MenuItem("List students", () -> listStudents()));
        menu.addMenuItem(new MenuItem("Add media", () -> addMedia()));
        menu.addMenuItem(new MenuItem("List media", () -> listMedia()));
        menu.addMenuItem(new MenuItem("Play media", () -> playMedia()));
        menu.addMenuItem(new MenuItem("List points", () ->listAvailablePoints()));
        menu.addMenuItem(new MenuItem("Buy points", () -> buyPoints()));
        menu.addMenuItem(new MenuItem("Exit", () -> endApp()));
    }
    public static void main(String[] args) {
        Main inst = new Main();
        inst.mdi();
    }

    private Integer selectFromMenu() {
        System.out.println("     []   [] >\n     []   [] >  >\n     []   [] >  >  >\n     []   [] >  >\n     []   [] >\n\n          MOES          \n" + menu + "\n" + output);
        output = "";
        return Menu.getInt("Selection? ");
    }

    private void mdi() {
        while(running) {
            try {
                Integer i = selectFromMenu();
                if(i == null)continue;
                menu.run(i);
            }catch (Exception e) {
                System.err.print(e + "\n");
            }
        }
    }
    private void endApp() {
        running = false;
    }
}
   


