package server;

import java.awt.AWTException;
import java.awt.MouseInfo;
import java.awt.Point;
import java.awt.Robot;
import java.awt.event.KeyEvent;

public class Driver {

    private Point startLocation;
    private Robot robot;

    public Driver() throws AWTException {
        robot = new Robot();
        startLocation = MouseInfo.getPointerInfo().getLocation();
    }
    
    public void updatePosition(int dx, int dy) {
        robot.mouseMove(startLocation.x + dx, startLocation.y + dy);
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
