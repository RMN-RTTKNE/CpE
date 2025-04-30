public class TestAccount {
    public static void main(String[] args) {
       Account firstAccount = new Account();
       Account secondAccount = new Account();

       if(firstAccount.getAccountNumber() != 1 || secondAccount.getAccountNumber() !=2) {
        System.err.println("FAIL: Account 1 = 1 and Account 2 = 2 but Account 1 = " + firstAccount.getAccountNumber() + " and Account 2 = " + secondAccount.getAccountNumber());
        System.exit(1);
       }
        
    }
}