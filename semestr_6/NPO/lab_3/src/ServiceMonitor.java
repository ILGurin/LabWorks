import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.logging.FileHandler;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.logging.SimpleFormatter;

public class ServiceMonitor {
    private final Logger logger = Logger.getLogger(ServiceMonitor.class.getName());
    private final int maxRestartAttempts;
    private final long restartDelayMs;
    private final AtomicInteger restartAttempts = new AtomicInteger(0);

    public ServiceMonitor(int maxRestartAttempts, long restartDelayMs) {
        this.maxRestartAttempts = maxRestartAttempts;
        this.restartDelayMs = restartDelayMs;
        try {
            String pattern = "yyyy-MM-dd-hh-mm-ss";
            SimpleDateFormat simpleDateFormat = new SimpleDateFormat(pattern);
            String date = simpleDateFormat.format(new Date());
            FileHandler fh = new FileHandler("ServiceMonitor_" + date + ".log", true);
            logger.addHandler(fh);
            fh.setFormatter(new SimpleFormatter());
        } catch (SecurityException | IOException e) {
            logger.log(Level.SEVERE, "Ошибка при работе с FileHandler.", e);
        }
    }

    public void startMonitoring() {
        Service service = new Service();
        new Thread(service).start();

        while (true) {
            if (!service.isRunning()) {
                if (restartAttempts.get() < maxRestartAttempts) {
                    try {
                        Thread.sleep(restartDelayMs);
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                        logger.info("Мониторинг прерван");
                        break;
                    }
                    logger.info("Попытка перезапуска сервиса...");
                    service.restart();
                    restartAttempts.incrementAndGet();
                } else {
                    logger.info("Достигнуто максимальное количество попыток перезапуска. Сервис не восстановлен.");
                    break;
                }
            } else {
                restartAttempts.set(0);
            }

            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                logger.info("Мониторинг прерван.");
                break;
            }
        }
    }
}
