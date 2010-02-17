package server;

import java.awt.AWTException;
import java.awt.DisplayMode;
import java.awt.GraphicsEnvironment;
import java.awt.MouseInfo;
import java.awt.Point;
import java.awt.Robot;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;

public class Driver {

    private static int[] buttons = { InputEvent.BUTTON1_MASK,
            InputEvent.BUTTON2_MASK, InputEvent.BUTTON3_MASK };
    private Point lastLocation;
    private Robot robot;
    private DisplayMode displayMode;

    public Driver() throws AWTException {
        robot = new Robot();
        lastLocation = MouseInfo.getPointerInfo().getLocation();
        displayMode = GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice().getDisplayMode();
    }
    
    public void updatePosition(int dx, int dy) {
        for (int i = 0; i < 5; i++) {
            lastLocation.x += dx / 5;
            lastLocation.y += dy / 5;
            if (lastLocation.x < 0) lastLocation.x = 0;
            if (lastLocation.y < 0) lastLocation.y = 0;
            if (lastLocation.x > displayMode.getWidth()) lastLocation.x = displayMode.getWidth();
            if (lastLocation.y > displayMode.getHeight()) lastLocation.y = displayMode.getHeight();
            robot.mouseMove(lastLocation.x, lastLocation.y);
            try {
                Thread.sleep(2);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public void click(int button) {
        button = buttons[button - 1];
        robot.mousePress(button);
        robot.mouseRelease(button);
    }

    public void scroll(int amount) {
        robot.mouseWheel(amount);
    }
    
    public void sendCharacters(String string) {
        for (int i = 0; i < string.length(); i++) {
            char letter = string.charAt(i);
            char upperCase = Character.toUpperCase(letter);
            boolean shift = letter == upperCase;
            if (shift) {
                robot.keyPress(KeyEvent.VK_SHIFT);
            }
            robot.keyPress(upperCase);
            robot.keyRelease(upperCase);
            if (shift) {
                robot.keyRelease(KeyEvent.VK_SHIFT);
            }
        }
    }
}
