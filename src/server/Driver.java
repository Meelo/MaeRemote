package server;

import java.awt.AWTException;
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

    public Driver() throws AWTException {
        robot = new Robot();
        lastLocation = MouseInfo.getPointerInfo().getLocation();
    }
    
    public void updatePosition(int dx, int dy) {
        lastLocation.x += dx;
        lastLocation.y += dy;
        robot.mouseMove(lastLocation.x, lastLocation.y);
    }

    public void click(int button) {
        robot.mousePress(buttons[button - 1]);
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
