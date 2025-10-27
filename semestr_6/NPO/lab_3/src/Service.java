import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.logging.FileHandler;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.logging.SimpleFormatter;

public class Service implements Runnable {
    private volatile boolean running = true;
    private final Logger logger = Logger.getLogger(ServiceMonitor.class.getName());

    public Service() {
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

    @Override
    public void run() {
        while (running) {
            try {
                Thread.sleep(500);
                logger.info("Сервис работает...");


                if (Math.random() < 0.5) {
                    throw new RuntimeException("Сервис упал!");
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                logger.info("Сервис прерван.");
                break;
            } catch (Exception e) {
                logger.log(Level.WARNING, e.getMessage());
                running = false;
                break;
            }
        }
    }

    public void restart() {
        running = true;
        new Thread(this).start();
    }

    public boolean isRunning() {
        return running;
    }
}