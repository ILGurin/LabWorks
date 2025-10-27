import java.math.BigDecimal;
import java.util.InputMismatchException;
import java.util.Scanner;

public class Main {
    private static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) {

        int a;
        while (true) {
            System.out.print("Введите int: ");
            try {
                a = sc.nextInt();
                break;
            } catch (InputMismatchException e) {
                System.out.println("Вы ввели не int! Пожалуйста введите int");
                sc.next();
            }
        }

        double b;
        while (true) {
            System.out.print("Введите double: ");
            try {
                b = sc.nextDouble();
                break;
            } catch (InputMismatchException e) {
                System.out.println("Вы ввели не double! Пожалуйста введите double");
                sc.next();
            }
        }

        boolean c;
        while (true) {
            System.out.print("Введите boolean: ");
            try {
                c = sc.nextBoolean();
                sc.reset();
                break;
            } catch (InputMismatchException e) {
                System.out.println("Вы ввели не boolean! Пожалуйста введите boolean");
                sc.next();
            }
        }

        BigDecimal d;
        while (true) {
            System.out.print("Введите bigDecimal: ");
            try {
                d = sc.nextBigDecimal();
                break;
            } catch (InputMismatchException e) {
                System.out.println("Вы ввели не bigDecimal! Пожалуйста введите bigDecimal");
                sc.next();
            }
        }

        String f;
        while (true) {
            System.out.print("Введите String: ");
            try {
                sc.next();
                f = sc.nextLine();
                break;
            } catch (InputMismatchException e) {
                System.out.println("Вы ввели не String! Пожалуйста введите String");
                sc.next();
            }
        }
//        HashMap<Integer, String> hash = new HashMap<>();
//        hash.put(0, "Введите int: ");
//        for (int i = 0; i < 5; i++) {
//            String str = hash.get(i);
//            System.out.print(str);
//        }
    }
}