import java.math.BigInteger;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        sc.close();
        
        BigInteger mod = BigInteger.valueOf(m);
        BigInteger a = BigInteger.ONE;
        BigInteger b = BigInteger.ZERO;
        
        System.out.print(0 + " ");
        
        for (int i = 2; i <= n; i++) {
            BigInteger c = BigInteger.valueOf(i - 1).multiply(a.add(b)).mod(mod);
            System.out.print(c + " ");
            a = b;
            b = c;
        }
        System.out.println();
    }
}
