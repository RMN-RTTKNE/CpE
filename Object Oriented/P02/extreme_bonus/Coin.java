public class Coin {
    private Denomination denomination;
    private int year;
    
    public Coin (Denomination denomination, int year) {
        this.denomination = denomination;
        this.year = year;
    }

    public double getValue() {
        return denomination.getValue();
    }

    public double getWeight() {
        double weight; 
        switch (denomination) {
            case PENNY -> {
                if(year > 1983)
                {weight = 2.500;} 
                else
                {weight = 3.110;}
            }
            case NICKEL -> weight = 5.000;
            case DIME -> {
                if(year > 1965)
                {weight = 2.268;} 
                else
                {weight = 2.500;}
            }
            case QUARTER -> {
                if(year > 1965)
                {weight = 5.670;} 
                else
                {weight = 6.250;}
            }
            default -> weight = 0;
        };

        return weight;
    }

    public int getYear() {
        return year;
    }
    @Override
    public String toString() {
        return year + " " + denomination.toString();
    }
}