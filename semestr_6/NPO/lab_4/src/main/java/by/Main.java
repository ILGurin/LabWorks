package by;

import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        List<String> tasks = new ArrayList<>();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            printMenu();
            int choice = readChoice(scanner);

            switch (choice) {
                case 1:
                    addTask(tasks, scanner);
                    break;
                case 2:
                    markTaskAsDone(tasks, scanner);
                    break;
                case 3:
                    deleteTask(tasks, scanner);
                    break;
                case 4:
                    showTasks(tasks);
                    break;
                case 5:
                    System.out.println("Exiting...");
                    scanner.close();
                    return;
                default:
                    System.out.println("Invalid choice! Please try again.");
            }
        }
    }

    private static void printMenu() {
        System.out.println("1. Add task");
        System.out.println("2. Mark task as done");
        System.out.println("3. Delete task");
        System.out.println("4. Show tasks");
        System.out.println("5. Exit");
    }

    private static int readChoice(Scanner scanner) {
        while (true) {
            try {
                System.out.print("Enter your choice: ");
                return scanner.nextInt();
            } catch (InputMismatchException e) {
                System.out.println("Invalid input! Please enter a number.");
                scanner.nextLine();
            }
        }
    }

    private static void addTask(List<String> tasks, Scanner scanner) {
        System.out.print("Enter task: ");
        scanner.nextLine();
        String task = scanner.nextLine();
        tasks.add(task);
        System.out.println("Task added!");
    }

    private static void markTaskAsDone(List<String> tasks, Scanner scanner) {
        int index = readIndex(scanner, tasks.size());
        if (index != -1) {
            tasks.set(index, tasks.get(index) + " (DONE)");
            System.out.println("Task marked as done!");
        }
    }

    private static void deleteTask(List<String> tasks, Scanner scanner) {
        int index = readIndex(scanner, tasks.size());
        if (index != -1) {
            tasks.remove(index);
            System.out.println("Task deleted!");
        }
    }

    private static void showTasks(List<String> tasks) {
        if (tasks.isEmpty()) {
            System.out.println("No tasks available.");
        } else {
            for (int i = 0; i < tasks.size(); i++) {
                System.out.println(i + ": " + tasks.get(i));
            }
        }
    }

    private static int readIndex(Scanner scanner, int size) {
        System.out.print("Enter task index: ");
        try {
            int index = scanner.nextInt();
            if (index >= 0 && index < size) {
                return index;
            } else {
                System.out.println("Invalid index! Please try again.");
                return -1;
            }
        } catch (InputMismatchException e) {
            System.out.println("Invalid input! Please enter a number.");
            scanner.nextLine();
            return -1;
        }
    }
}