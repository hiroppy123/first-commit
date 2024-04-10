// NumberManipulator.java

import java.util.Scanner;

public class NumberManipulator {

    private int num1;
    private int num2;

    public NumberManipulator(int num1, int num2) {
        this.num1 = num1;
        this.num2 = num2;
    }

    public int calculateSum() {
        return num1 + num2;
    }

    public int calculateProduct() {
        return num1 * num2;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Welcome to the Number Manipulator!");

        // Get input
        System.out.print("Enter first number: ");
        int num1 = scanner.nextInt();

        System.out.print("Enter second number: ");
        int num2 = scanner.nextInt();

        // Create NumberManipulator object
        NumberManipulator manipulator = new NumberManipulator(num1, num2);

        // Display results
        System.out.println("Sum: " + manipulator.calculateSum());
        System.out.println("Product: " + manipulator.calculateProduct());

        // Close scanner
        scanner.close();
    }
}

