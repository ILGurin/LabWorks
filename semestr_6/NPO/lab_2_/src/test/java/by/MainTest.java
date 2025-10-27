package by;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

public class MainTest {
    @Test
    public void reverseListDefaultTest() {
        for (int size = 1000000; size <= 10000000; size+= 1000000) {
            List<Integer> list = new ArrayList<>(size);
            for (int i = 0; i < size; i++) {
                list.add(i);
            }
            long startTime = System.currentTimeMillis();
            Main.reverseListDefault(list);
            long endTime = System.currentTimeMillis();
            System.out.println("Размер списка: " + size + ", Время реверса: " + (endTime - startTime) + " мс");
            list.clear();
        }

    }

}
