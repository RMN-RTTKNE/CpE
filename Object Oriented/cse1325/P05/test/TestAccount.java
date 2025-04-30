package test;
import customer.Account;
import customer.Student;

public class TestAccount {
    public static void main(String[] args) {
       Student a = new Student("John Connor", 1001001000, "email@uta.edu", true);
       Student b = new Student("Bruce Wayne", 2002002000, "email@mavs.uta.edu", false);

       if(a.getAccount().getAccountNumber() != 1 || b.getAccount().getAccountNumber() !=2) {
        System.err.println("FAIL: Account 1 = 1 and Account 2 = 2 but Account 1 = " + a.getAccount().getAccountNumber() + " and Account 2 = " + b.getAccount().getAccountNumber());
        System.exit(1);
       }
        
    }
}