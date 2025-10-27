
public class Main {
    private static final int MAX_RESTART_ATTEMPTS = 3;
    private static final long RESTART_DELAY_MS = 1000;

    public static void main(String[] args) {
        ServiceMonitor monitor = new ServiceMonitor(MAX_RESTART_ATTEMPTS, RESTART_DELAY_MS);
        monitor.startMonitoring();
    }
}