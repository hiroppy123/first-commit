public class HundredDoors2 {
    public static void main(String[] args) {
        boolean[] doors = new boolean[101]; // Array to represent doors (index 0 is unused)
        
        // Perform 100 passes
        for (int pass = 1; pass <= 100; pass++) {
            for (int i = pass; i <= 100; i += pass) {
                doors[i] = !doors[i]; // Toggle the door
            }
        }
        
        // Print the state of the doors
        for (int i = 1; i <= 100; i++) {
            System.out.println("Door " + i + " is " + (doors[i] ? "open" : "closed"));
        }
    }
}




