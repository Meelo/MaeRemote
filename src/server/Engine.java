package server;

import java.awt.AWTException;
import java.awt.event.KeyEvent;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class Engine implements Runnable {
    private Driver driver;
    private BlockingQueue<String> commandQueue;
    private Thread commandThread;

    public static final char CMD_SPLIT_CHAR = 255;
    private static final String UPDATE_COMMAND = "U";
    private static final String MESSAGE_COMMAND = "M";
    private static final String CLICK_COMMAND = "C";
    private static final String SCROLL_COMMAND = "S";
    private static final String SHUTDOWN_REQUEST = "shutdown";
    
    private static final String HOLD = "__HOLD_";
    private static final String RELEASE = "__RELEASE_";
    private static final String LEFT = "LEFT__";
    private static final String UP = "UP__";
    private static final String RIGHT = "RIGHT__";
    private static final String DOWN = "DOWN__";
    private static final Map<String, Integer> arrowMap = new HashMap<String, Integer>();

    static {
        arrowMap.put(LEFT, KeyEvent.VK_LEFT);
        arrowMap.put(UP, KeyEvent.VK_UP);
        arrowMap.put(RIGHT, KeyEvent.VK_RIGHT);
        arrowMap.put(DOWN, KeyEvent.VK_DOWN);
    }
    
    public Engine() throws AWTException {
        this.driver = new Driver();
        this.commandQueue = new LinkedBlockingQueue<String>();
        this.commandThread = new Thread(this);
        this.commandThread.start();
    }

    public void addCommand(String command) {
        commandQueue.add(command);
    }

    public void run() {
        String command;

        try {
            while (!SHUTDOWN_REQUEST.equals(command = commandQueue.take())) {
                parseAndProcessCommand(command);
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }        

    public void stop() {
        commandQueue.add(SHUTDOWN_REQUEST);
    }

    private void parseAndProcessCommand(String commandLine) {
        String[] inputArray = commandLine.split(Character.toString(CMD_SPLIT_CHAR));
        try {
            String command = inputArray[0];
            if (UPDATE_COMMAND.equals(command)) {
                // U;dx;dy
                int dx = Integer.parseInt(inputArray[1]);
                int dy = Integer.parseInt(inputArray[2]);
                boolean fastMode = !commandQueue.isEmpty();
                updatePosition(dx, dy, fastMode);
            }
            else if (MESSAGE_COMMAND.equals(command) && inputArray.length > 1) {
                // M;character/string
                if (inputArray[1].equals("__RETURN__")) {
                    sendCharacters("\n");
                }
                else if (inputArray[1].startsWith(HOLD)) {
                    holdKey(inputArray[1].substring(HOLD.length()));
                }
                else if (inputArray[1].startsWith(RELEASE)) {
                    releaseKey(inputArray[1].substring(RELEASE.length()));
                }
                else {
                    sendCharacters(inputArray[1]);
                }
            }
            else if (CLICK_COMMAND.equals(command)) {
                // C;button
                click(Integer.parseInt(inputArray[1]));
            }
            else if (SCROLL_COMMAND.equals(command)) {
                // S;amount
                scroll(Integer.parseInt(inputArray[1]));
            }
            else {
                System.err.println("Unknown command: " + commandLine);
            }
        }
        catch (Exception e) {
            System.err.println("Error while parsing a command: " + commandLine);
            e.printStackTrace();
        }        
    }

    private void releaseKey(String key) {
        driver.releaseKey(arrowMap.get(key));
    }

    private void holdKey(String key) {
        driver.holdKey(arrowMap.get(key));
    }

    public void log(String string) {
        System.out.println(string);
    }

    public void updatePosition(int dx, int dy, boolean fastMode) {
        driver.updatePosition(dx, dy, fastMode);
    }

    public void click(int button) {
        driver.click(button);
    }

    public void scroll(int amount) {
        driver.scroll(amount);
    }

    public void sendCharacters(String string) {
        driver.sendCharacters(string);
    }
}
