// BadProgram.java

public class BadProgram {

    public static void main(String[] args) {
        System.out.println("Welcome to the Number Manipulator!");

        // Get input
        System.out.print("Enter first number: ");
        int num1 = Integer.parseInt(System.console().readLine());

        System.out.print("Enter second number: ");
        int num2 = Integer.parseInt(System.console().readLine());

        // Perform operations
        int sum = num1 + num2;
        int product = num1 * num2;

        // Display results
        System.out.println("Sum: " + sum);
        System.out.println("Product: " + product);
    }
}

