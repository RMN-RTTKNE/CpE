public class TestStudent {
    public static void main(String[] args) {
        Student student = new Student("John Connor", 1002003000, "email@uta.edu");
        Account testacc = new Account();
        if(!student.toString().equals("John Connor (1002003000, email@uta.edu, Account #1)")) {
            System.err.println("FAIL: John Connor (1002003000, email@uta.edu, Account #1), but " + student.toString()); 
        } 
    }
}