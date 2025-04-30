package mdi;
import moes.Moes;
import customer.Student;
import product.Media;
import java.util.Scanner;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.FileReader;
import java.io.FileWriter;

public class Main {
    private Moes moes;
    private String output;
    private Menu menu;
    private boolean running;
    private String filename;
    private static final String extension = ".txt";
    private static final String magicCookie = "MAGIC_FILE";
    private static final String fileVersion = "Version 1.0";
    private static boolean dirty = false;



    private void addStudent() {
        String name = Menu.getString("Enter student name: ", ""); if(name == null) return; else dirty = true;
        Integer id = Menu.getInt("Enter student ID #: ", ""); if(id == null) return; else dirty = true;
        String email = Menu.getString("Enter student email: ", ""); if(email == null) return; else dirty = true;
        Boolean unlimited = Menu.getBoolean("Enter unlimited status: ", ""); if(unlimited == null) return; else dirty = true;

        Student student = new Student(name, id, email, unlimited);
        moes.addStudent(student);
    }
    private void listStudents() {
        System.out.println(moes.getStudentList());
    }

    private void addMedia() {
        String title = Menu.getString("Enter media title: ", ""); if(title == null) return; else dirty = true;
        String url = Menu.getString("Enter media URL: ", ""); if(url == null) return; else dirty = true;
        Integer points = Menu.getInt("Enter media points: ", ""); if(points == null) return; else dirty = true;

        Media media = new Media(title, url, points);
        moes.addMedia(media);
    }
    private void listMedia() {
        System.out.println(moes.getMediaList());
    }
    private void playMedia() {
        Integer sndx = Menu.getInt("Enter student index: ", ""); if(sndx == null) return; else dirty = true;
        Integer mndx = Menu.getInt("Enter media index: ", "");  if(mndx == null) return; else dirty = true;

        System.out.println(moes.playMedia(sndx, mndx));
    }
    private void listAvailablePoints() {
        Integer sndx2 = Menu.getInt("Enter student index: ", "");  if(sndx2 == null) return; else dirty = true;

        System.out.println("Student has " + moes.getPoints(sndx2) + " points");
    }
    private void buyPoints() {
        Integer sndx3 = Menu.getInt("Enter student index: ", "");  if(sndx3 == null) return; else dirty = true;
        System.out.println("Available points: " + moes.getPoints(sndx3));
        Integer bpoint = Menu.getInt("How many points to buy? ", "");  if(bpoint == null) return; else dirty = true;
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
        menu.addMenuItem(new MenuItem("New Moes", () -> newMoes()));
        menu.addMenuItem(new MenuItem("Save", () -> save()));
        menu.addMenuItem(new MenuItem("Save As", () -> saveAs()));
        menu.addMenuItem(new MenuItem("Open", () -> open()));

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

    private void newMoes() {
        dirtycheck();
        moes = new Moes();
        dirty = false;
    }

    private void save() {
        try(BufferedWriter bw = new BufferedWriter(new FileWriter(filename))) {
            bw.write(magicCookie + '\n');
            bw.write(fileVersion + '\n');
            moes.save(bw);
            dirty = false;
            return;
        } catch (Exception e) {
            System.err.println("Failed to write: " + e);
            return;
        }
    }

    private void saveAs() {
        System.out.println("Current file name: " + filename); 
        String filein = Menu.getString("Enter new file name: ", ""); if(filein == null) return;
        if(!filein.contains(".")) {
            filein += extension;
        }
        filename = filein;
        save();
    }

    private void open() {
        dirtycheck();
        System.out.println("Current file name: " + filename); 
        String filein = Menu.getString("Enter new file name: ", ""); if(filein == null) return;
        if(!filein.contains(".")) {
            filein += ".txt";
        }
        try(BufferedReader br = new BufferedReader(new FileReader(filein))) {
            String check1 = br.readLine();
            String check2 = br.readLine();
            if((check1 + '\n').equals(magicCookie)) throw new IOException("Magic cookie not first line"); 
            else if((check2 + '\n').equals(fileVersion)) throw new IOException("File version not second line");
            
            Moes stream = new Moes(br);
            moes = stream;

        } catch (IOException e) {
            System.err.println("Failed to write: " + e);
            return;
        } catch (Exception e) {
            System.err.println("Failed to reconstruct new Moes from stream: " + e);
            return;
        }
        filename = filein;
        dirty = false;
    }

    private void dirtycheck() {
        if(dirty) { 
            Integer dirt = Menu.getInt("WARNING: Unsaved data.\n(0) Save to current file\n(1) Save to new file\n(2) Discard changed data\n");
            switch (dirt) {
                case 0 -> save();
                case 1 -> saveAs();
                default -> {return;}
            }
        }
         dirty = false;
    }
}
   


