public class Purse{
    public static void main(String[] args) {
    Coin[] arr = {
    new Coin(Denomination.PENNY, 1996),
    new Coin(Denomination.NICKEL, 1962),
    new Coin(Denomination.DIME, 2001),
    new Coin(Denomination.QUARTER,2017),
    new Coin(Denomination.QUARTER, 1901)
    };

    double total = 0;
    for(Coin coin : arr) {
        total += coin.getValue();
    }

    int max = 0;
    int min = 3000;
    for(Coin coin : arr) {
        int year = coin.getYear();
        if(year < min) {
            min = year;
        }
        if(year > max) {
            max = year;
        }
    }

    System.out.printf("You have $ %.2f in coins between %d and %d\n", total, min, max);
    }
}