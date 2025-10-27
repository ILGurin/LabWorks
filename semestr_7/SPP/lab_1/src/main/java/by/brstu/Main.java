package by.brstu;

import redis.clients.jedis.Jedis;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.UUID;

public class Main {
    private static final String REDIS_LOG_LIST_KEY = "app_logs";
    private static final String instanceId = UUID.randomUUID().toString();

    public static void main(String[] args) {
        System.out.println("Instance ID: " + instanceId);

        try (Jedis jedis = new Jedis("localhost", 6379)) {
            for (int i = 1; i <= 10; i++) {
                String log = generateLog(i);
                jedis.rpush(REDIS_LOG_LIST_KEY, log);
                System.out.println("Log added: " + log);
                Thread.sleep(500);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            System.err.println("Interrupted");
        }
    }

    private static String generateLog(int id) {
        String timestamp = LocalDateTime.now().format(DateTimeFormatter.ISO_LOCAL_DATE_TIME);
        return String.format("[%s] %s - Log entry #%d", instanceId, timestamp, id);
    }
}