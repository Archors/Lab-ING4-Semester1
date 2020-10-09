package company;

import model.DataAccess;

public class Main {

    public static void main(String[] args) {
        DataAccess data = new DataAccess(args[0], args[1], args.length < 3 ? "" : args[2]);
    }
}
