package by;

import org.junit.jupiter.api.Test;
import java.util.ArrayList;
import java.util.List;
import static org.junit.jupiter.api.Assertions.*;

public class MainTest {

    @Test
    public void testAddTask() {
        List<String> tasks = new ArrayList<>();
        String task = "New Task";

        tasks.add(task);

        assertEquals(1, tasks.size());
        assertEquals("New Task", tasks.get(0));
    }

    @Test
    public void testDeleteTask() {
        List<String> tasks = new ArrayList<>();
        tasks.add("Task 1");
        tasks.add("Task 2");

        tasks.remove(0);

        assertEquals(1, tasks.size());
        assertEquals("Task 2", tasks.get(0));
    }

    @Test
    public void testShowTasks() {
        List<String> tasks = new ArrayList<>();
        tasks.add("Task 1");
        tasks.add("Task 2");

        assertEquals(2, tasks.size());
        assertTrue(tasks.contains("Task 1"));
        assertTrue(tasks.contains("Task 2"));
    }

    @Test
    public void testMarkTaskAsDone() {
        List<String> tasks = new ArrayList<>();
        tasks.add("Task 1");

        tasks.set(0, tasks.get(0) + " (DONE)");

        assertEquals("Task 1 (DONE)", tasks.get(0));
    }
}

