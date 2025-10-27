package by;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        List<Integer> originalList = new ArrayList<>();
        for (int i = 0; i < 10; i++) {
            originalList.add(i);
        }
        List<Integer> reversedList = reverseListDefault(originalList);
        System.out.println(reversedList);
    }

    public static <T> List<T> reverseListDefault(List<T> list) {
        List<T> reversed = new ArrayList<T>(list);
        Collections.reverse(reversed);
        return reversed;
    }
}