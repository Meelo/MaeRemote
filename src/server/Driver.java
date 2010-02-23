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
    private static final int MOVE_STEPS = 5;
    
    public Driver() throws AWTException {
        robot = new Robot();
        lastLocation = MouseInfo.getPointerInfo().getLocation();
        displayMode = GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice().getDisplayMode();
    }
    
    public void updatePosition(int dx, int dy, boolean fastMode) {
        if (fastMode) {
            movePosition(dx, dy);
        }
        else {
            int targetX = validateXCoord(lastLocation.x + dx);
            int targetY = validateYCoord(lastLocation.y + dy);
            int stepsLeft = MOVE_STEPS;
            while (stepsLeft > 0) {
                int xStep = (targetX - lastLocation.x) / stepsLeft;
                int yStep = (targetY - lastLocation.y) / stepsLeft;
                movePosition(xStep, yStep);
                try {
                    Thread.sleep(5);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                stepsLeft--;
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

    private void movePosition(int dx, int dy) {
        lastLocation.x = validateXCoord(lastLocation.x + dx);
        lastLocation.y = validateYCoord(lastLocation.y + dy);
        robot.mouseMove(lastLocation.x, lastLocation.y);        
    }
    
    private int validateXCoord(int x) {
        return validateCoord(x, displayMode.getWidth());
    }

    private int validateYCoord(int y) {
        return validateCoord(y, displayMode.getHeight());
    }

    private int validateCoord(int coord, int limit) {
        if (coord > limit) {
            coord = limit;
        }
        else if (coord < 0) {
            coord = 0;
        }
        return coord;
    }
}