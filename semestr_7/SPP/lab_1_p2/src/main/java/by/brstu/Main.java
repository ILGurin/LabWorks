package by.brstu;

import redis.clients.jedis.Jedis;

public class Main {
    private static final String REDIS_LOG_LIST_KEY = "app_logs";

    public static void main(String[] args) {
        try (Jedis jedis = new Jedis("localhost", 6379)) {
            String log;
            while ((log = jedis.lpop(REDIS_LOG_LIST_KEY)) != null) {
                System.out.println(log);
            }
        }
    }
}

