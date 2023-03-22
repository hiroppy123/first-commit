import java.util.Scanner;

class Student {

    String name, birth, state;
    int old;

    void changeName(String name) {
        this.name = name;
    }
}

public class Main {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        int k = sc.nextInt();

        Student[] students = new Student[n];
        for (int i = 0; i < n; i++) {
            students[i] = new Student();
            students[i].name = sc.next();
            students[i].old = sc.nextInt();
            students[i].birth = sc.next();
            students[i].state = sc.next();
        }

        for (int i = 0; i < k; i++) {
            int a = sc.nextInt() - 1;
            String nn = sc.next();
            students[a].changeName(nn);
        }

        for (Student student : students) {
            System.out.println(
                student.name +
                " " +
                student.old +
                " " +
                student.birth +
                " " +
                student.state
            );
        }
    }
}
